/*
	PSX VAG-Packer & VAG-Depack, hacked by bITmASTER@bigfoot.com
	V0.1
	Modified for use with trmod by b122251
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "vag.h"
char *vag(char *wav){
	#define BUFFER_SIZE 128*28
	short wave[BUFFER_SIZE];
	FILE *fp;
	short *ptr;
	double d_samples[28];
	short four_bit[28];
	int predict_nr;
	int shift_factor;
	int flags;
	int size;
	int i, j, k;   
	unsigned char d;
	int sample_len;
	unsigned freeuint1=20;
	fp = fopen( wav, "rb" );
	fseek( fp, 40, SEEK_SET );
	fread( &sample_len, 4, 1, fp );
	sample_len /= 2;
	char *vag=malloc(20);
	memset(vag,0,20);
	flags = 0; 
	while( sample_len > 0 ) {
		size = ( sample_len >= BUFFER_SIZE ) ? BUFFER_SIZE : sample_len;
		fread( wave, sizeof( short ), size, fp );
		i = size / 28;
		if ( size % 28 ) {
			for ( j = size % 28; j < 28; j++ )
				wave[28*i+j] = 0;
			i++;
		}
		for ( j = 0; j < i; j++ ) {
			ptr = wave + j * 28;
			vag_find_predict( ptr, d_samples, &predict_nr, &shift_factor );
			vag_pack( d_samples, four_bit, predict_nr, shift_factor );
			d = ( predict_nr << 4 ) | shift_factor;
			vag = (char *) realloc(vag,(freeuint1+2));
			memcpy(vag+freeuint1,&d,1);
			memcpy(vag+freeuint1+1,&flags,1);
			freeuint1+=2;
			for ( k = 0; k < 28; k += 2 ) {
				d = ( ( four_bit[k+1] >> 8 ) & 0xf0 ) | ( ( four_bit[k] >> 12 ) & 0xf );
				vag = (char *) realloc(vag,(freeuint1+1));
				memcpy(vag+freeuint1,&d,1);
				freeuint1++;
			}
			sample_len -= 28;
			if ( sample_len < 28 )
				flags = 1;
		}
	}
	vag = (char *) realloc(vag,(freeuint1+16));
	predict_nr <<=4 ;
	predict_nr |=shift_factor;
	memcpy(vag+freeuint1,&predict_nr,1);
	memset(vag+freeuint1+1,7,1);
	freeuint1+=2;
	memset(vag+freeuint1,0,14);
	freeuint1+=10;
	fclose( fp );
	memcpy(vag,&freeuint1,4);
	return(vag);
}
static double f[5][2] = { { 0.0, 0.0 },
							{  -60.0 / 64.0, 0.0 },
							{ -115.0 / 64.0, 52.0 / 64.0 },
							{  -98.0 / 64.0, 55.0 / 64.0 },
							{ -122.0 / 64.0, 60.0 / 64.0 } };
void vag_find_predict( short *samples, double *d_samples, int *predict_nr, int *shift_factor )
{
	int i, j;
	double buffer[28][5];
	double min = 1e10;
	double max[5];
	double ds;
	int min2;
	int shift_mask;
	static double _s_1 = 0.0;
	static double _s_2 = 0.0;
	double s_0, s_1, s_2;
	for ( i = 0; i < 5; i++ ) {
		max[i] = 0.0;
		s_1 = _s_1;
		s_2 = _s_2;
		for ( j = 0; j < 28; j ++ ) {
			s_0 = (double) samples[j];
			if ( s_0 > 30719.0 )
				s_0 = 30719.0;
			if ( s_0 < - 30720.0 )
				s_0 = -30720.0;
			ds = s_0 + s_1 * f[i][0] + s_2 * f[i][1];
			buffer[j][i] = ds;
			if ( fabs( ds ) > max[i] )
				max[i] = fabs( ds );
				s_2 = s_1;
				s_1 = s_0;
		}
		if ( max[i] < min ) {
			min = max[i];
			*predict_nr = i;
		}
		if ( min <= 7 ) {
			*predict_nr = 0;
			break;
		}
	}
	_s_1 = s_1;
	_s_2 = s_2;
	for ( i = 0; i < 28; i++ )
		d_samples[i] = buffer[i][*predict_nr];
	min2 = ( int ) min;
	shift_mask = 0x4000;
	*shift_factor = 0;
	while( *shift_factor < 12 ) {
		if ( shift_mask  & ( min2 + ( shift_mask >> 3 ) ) )
			break;
		(*shift_factor)++;
		shift_mask = shift_mask >> 1;
	}
}
void vag_pack( double *d_samples, short *four_bit, int predict_nr, int shift_factor )
{
	double ds;
	int di;
	double s_0;
	static double s_1 = 0.0;
	static double s_2 = 0.0;
	int i;
	for ( i = 0; i < 28; i++ ) {
		s_0 = d_samples[i] + s_1 * f[predict_nr][0] + s_2 * f[predict_nr][1];
		ds = s_0 * (double) ( 1 << shift_factor );
		di = ( (int) ds + 0x800 ) & 0xfffff000;
		if ( di > 32767 )
			di = 32767;
		if ( di < -32768 )
			di = -32768;
		four_bit[i] = (short) di;
		di = di >> shift_factor;
		s_2 = s_1;
		s_1 = (double) di - s_0;
	}
}
char *unvag(char *vag, unsigned vaglength){
	double f[5][2] = { { 0.0, 0.0 },
					{  60.0 / 64.0,  0.0 },
					{  115.0 / 64.0, -52.0 / 64.0 },
					{  98.0 / 64.0, -55.0 / 64.0 },
					{  122.0 / 64.0, -60.0 / 64.0 } };
	double samples[28];
	int predict_nr, shift_factor, flags;
	int i;
	int d, s;
	int e;
	static double s_1 = 0.0;
	static double s_2 = 0.0;
	unsigned freeuint1=64;
	unsigned freeuint2=44;
	char *pcm = malloc(freeuint2);
	memset(pcm,0,44); 
	while(freeuint1<=vaglength) {
		predict_nr=0;
		memcpy(&predict_nr,vag+freeuint1,1);
		freeuint1++;
		shift_factor = predict_nr & 0xf;
		predict_nr >>= 4;
		flags=0;
		memcpy(&flags,vag+freeuint1,1);
		freeuint1++;
		if ( flags == 7 )
			break;			 
		for ( i = 0; i < 28; i += 2 ) {
			d=0;
			memcpy(&d,vag+freeuint1,1);
			freeuint1++;
			s = ( d & 0xf ) << 12;
			if ( s & 0x8000 )
				s |= 0xffff0000;
			samples[i] = (double) ( s >> shift_factor  );
			s = ( d & 0xf0 ) << 8;
			if ( s & 0x8000 )
				s |= 0xffff0000;
			samples[i+1] = (double) ( s >> shift_factor  );
		}
		for ( i = 0; i < 28; i++ ) {
			samples[i] = samples[i] + s_1 * f[predict_nr][0] + s_2 * f[predict_nr][1];
			s_2 = s_1;
			s_1 = samples[i];
			d = (int) ( samples[i] + 0.5 );
			pcm = (char *) realloc(pcm,(freeuint2+2));
			e = d&0xff;
			memcpy(pcm+freeuint2,&e,1);
			d >>= 8;
			memcpy(pcm+freeuint2+1,&d,1);
			freeuint2+=2;
		}
	}
	memcpy(pcm,&freeuint2,4);
	return pcm;
}
