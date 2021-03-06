/*
*				sample.h
*
* Include file for sample.c.
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*
*	This file part of:	PSFEx
*
*	Copyright:		(C) 1997-2016 IAP/CNRS/UPMC
*
*	License:		GNU General Public License
*
*	PSFEx is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
* 	(at your option) any later version.
*	PSFEx is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*	You should have received a copy of the GNU General Public License
*	along with PSFEx.  If not, see <http://www.gnu.org/licenses/>.
*
*	Last modified:		12/10/2016
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifndef _CONTEXT_H_
#include "context.h"
#endif

#ifndef _SAMPLE_H_
#define _SAMPLE_H_

/*--------------------------------- constants -------------------------------*/

#define	LSAMPLE_DEFSIZE		1000	/* Sample stacksize at the beginning */
#define	RECENTER_NITERMAX	16	/* Max. number of recentering steps */
#define	RECENTER_NSIG		4	/* Recentering measurement radius */
#define	RECENTER_OVERSAMP	3	/* Oversampling for recentering */
#define	RECENTER_STEPMIN	0.001	/* Min. recentering coordinate update */
#define	RECENTER_GRADFAC	2.0	/* Gradient descent accel. factor */

/*-------------------------------- flags ------------------------------------*/

#define	BAD_CHI2	0x0001
#define	BAD_SEXFLAG	0x0002
#define	BAD_WEIGHTFLAG	0x0004
#define	BAD_IMAFLAG	0x0008
#define	BAD_SNR		0x0010
#define	BAD_SIZE	0x0020
#define	BAD_ELLIP	0x0040
#define	BAD_PIXEL	0x0080

/*--------------------------- structure definitions -------------------------*/

typedef struct sample
  {
  int		detindex;		/* Detection index */
  int		extindex;		/* Extension index */
  int		catindex;		/* Catalogue index */
  float		*vig;			/* Vignette array */
  float		*vigresi;		/* Residual-map of the PSF-residuals */
  float		*vigchi;		/* Chi-map of the PSF-residuals */
  float		*vigweight;		/* Vignette-weight array */
  float		*vigdgeox;		/* Vignette diff geo x-map array */
  float		*vigdgeoy;		/* Vignette diff geo y-map array */
  float		norm;			/* Normalisation */
  float		fwhm;			/* Source FWHM (derived from ) */
  float		ellip;			/* Source ellipticity */
  float		snr;			/* Source Signal-to-Noise ratio */
  double	x,y;			/* x,y position estimate in frame */
  float		dx,dy;			/* x,y shift / vignet center */
  float		backnoise2;		/* Variance of the background noise */
  float		gain;			/* conversion factor (e-/ADU) */
  float		chi2;			/* Chi2 of the fit */
  float		modresi;		/* Residual index */
  double	*context;		/* Context vector */
  int		badflag;		/* True if sample is discarded */
  }	samplestruct;

typedef struct set
  {
  char		*head;			/* Table structure */
  struct sample	*sample;		/* Array of samples */
  int		nsample;		/* Number of samples in stack */
  int		ngood;			/* Number of "good" samples */
  int		nsamplemax;		/* Max number of samples in stack */
  int		*vigsize;		/* Dimensions of vignette frames */
  int		vigdim;			/* Dimensionality of the vignette */
  int		nvig;			/* Number of pixels of the vignette */
  int		ncontext;		/* Number of contexts */
  char		**contextname;		/* List of context keywords used */
  double	*contextoffset;		/* Offset to apply to context data */
  double	*contextscale;		/* Scaling to apply to context data */
  float		fwhm;			/* FWHM of the PSF core */
  int		badflags;		/* # discarded with bad SEx flags */
  int		badwflags;		/* # discarded with bad SEx flags */
  int		badimaflags;		/* # discarded with bad SEx flags */
  int		badsn;			/* # discarded with S/N too low*/
  int		badfwhmmin;		/* # discarded with size too small */
  int		badfwhmmax;		/* # discarded with size too large */
  int		badellip;		/* # discarded with too much ellipt. */
  int		badpix;			/* # discarded with too many bad pix. */
  }	setstruct;

/*-------------------------------- protos -----------------------------------*/

samplestruct	*remove_sample(setstruct *set, int isample);

setstruct	*init_set(contextstruct *context),
		*load_samples(char **filename, int catindex, int ncat,
			int ext, int next, contextstruct *context),
		*read_samples(setstruct *set, char *filename,
			float frmin, float frmax,
			int ext, int next, int catindex,
			contextstruct *context, double *pcval);

void		add_set(setstruct *destset, setstruct *set),
		end_set(setstruct *set),
		free_samples(setstruct *set),
		free_samplevig(samplestruct *sample),
 		malloc_samples(setstruct *set, int nsample),
		malloc_samplevig(samplestruct *sample, int npix, int dgeoflag),
		make_weights(setstruct *set, samplestruct *sample),
		realloc_samples(setstruct *set, int nsample),
		recenter_sample(samplestruct *sample, setstruct *set,
			float fluxrad);

#endif

