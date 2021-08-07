#ifndef VAG_H_INCLUDED
#define VAG_H_INCLUDED

char *vag(char *wav);
void vag_find_predict( short *samples, double *d_samples, int *predict_nr, int *shift_factor );
void vag_pack( double *d_samples, short *four_bit, int predict_nr, int shift_factor );
char *unvag(char *vag, unsigned vaglength);

#endif
