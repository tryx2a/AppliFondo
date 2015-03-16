/* dgetri.f -- translated by f2c (version 20061008).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "pnl/pnl_f2c.h"

/* Table of constant values */

static int c__1 = 1;
static int c_n1 = -1;
static int c__2 = 2;
static double c_b20 = -1.;
static double c_b22 = 1.;

 int dgetri_(int *n, double *a, int *lda, int 
	*ipiv, double *work, int *lwork, int *info)
{
    /* System generated locals */
    int a_dim1, a_offset, i__1, i__2, i__3;

    /* Local variables */
    int i__, j, jb, nb, jj, jp, nn, iws;
    extern  int dgemm_(char *, char *, int *, int *, 
	    int *, double *, double *, int *, double *, 
	    int *, double *, double *, int *),
	     dgemv_(char *, int *, int *, double *, double *, 
	    int *, double *, int *, double *, double *, 
	    int *);
    int nbmin;
    extern  int dswap_(int *, double *, int *, 
	    double *, int *), dtrsm_(char *, char *, char *, char *, 
	    int *, int *, double *, double *, int *, 
	    double *, int *), xerbla_(
	    char *, int *);
    extern int ilaenv_(int *, char *, char *, int *, int *, 
	    int *, int *);
    int ldwork;
    extern  int dtrtri_(char *, char *, int *, double 
	    *, int *, int *);
    int lwkopt;
    int lquery;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGETRI computes the inverse of a matrix using the LU factorization */
/*  computed by DGETRF. */

/*  This method inverts U and then computes inv(A) by solving the system */
/*  inv(A)*L = inv(U) for inv(A). */

/*  Arguments */
/*  ========= */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the factors L and U from the factorization */
/*          A = P*L*U as computed by DGETRF. */
/*          On exit, if INFO = 0, the inverse of the original matrix A. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= MAX(1,N). */

/*  IPIV    (input) INTEGER array, dimension (N) */
/*          The pivot indices from DGETRF; for 1<=i<=N, row i of the */
/*          matrix was interchanged with row IPIV(i). */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK)) */
/*          On exit, if INFO=0, then WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK.  LWORK >= MAX(1,N). */
/*          For optimal performance LWORK >= N*NB, where NB is */
/*          the optimal blocksize returned by ILAENV. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */
/*          > 0:  if INFO = i, U(i,i) is exactly zero; the matrix is */
/*                singular and its inverse could not be computed. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipiv;
    --work;

    /* Function Body */
    *info = 0;
    nb = ilaenv_(&c__1, "DGETRI", " ", n, &c_n1, &c_n1, &c_n1);
    lwkopt = *n * nb;
    work[1] = (double) lwkopt;
    lquery = *lwork == -1;
    if (*n < 0) {
	*info = -1;
    } else if (*lda < MAX(1,*n)) {
	*info = -3;
    } else if (*lwork < MAX(1,*n) && ! lquery) {
	*info = -6;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGETRI", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0) {
	return 0;
    }

/*     Form inv(U).  If INFO > 0 from DTRTRI, then U is singular, */
/*     and the inverse is not computed. */

    dtrtri_("Upper", "Non-unit", n, &a[a_offset], lda, info);
    if (*info > 0) {
	return 0;
    }

    nbmin = 2;
    ldwork = *n;
    if (nb > 1 && nb < *n) {
/* Computing MAX */
	i__1 = ldwork * nb;
	iws = MAX(i__1,1);
	if (*lwork < iws) {
	    nb = *lwork / ldwork;
/* Computing MAX */
	    i__1 = 2, i__2 = ilaenv_(&c__2, "DGETRI", " ", n, &c_n1, &c_n1, &
		    c_n1);
	    nbmin = MAX(i__1,i__2);
	}
    } else {
	iws = *n;
    }

/*     Solve the equation inv(A)*L = inv(U) for inv(A). */

    if (nb < nbmin || nb >= *n) {

/*        Use unblocked code. */

	for (j = *n; j >= 1; --j) {

/*           Copy current column of L to WORK and replace with zeros. */

	    i__1 = *n;
	    for (i__ = j + 1; i__ <= i__1; ++i__) {
		work[i__] = a[i__ + j * a_dim1];
		a[i__ + j * a_dim1] = 0.;
/* L10: */
	    }

/*           Compute current column of inv(A). */

	    if (j < *n) {
		i__1 = *n - j;
		dgemv_("No transpose", n, &i__1, &c_b20, &a[(j + 1) * a_dim1 
			+ 1], lda, &work[j + 1], &c__1, &c_b22, &a[j * a_dim1 
			+ 1], &c__1);
	    }
/* L20: */
	}
    } else {

/*        Use blocked code. */

	nn = (*n - 1) / nb * nb + 1;
	i__1 = -nb;
	for (j = nn; i__1 < 0 ? j >= 1 : j <= 1; j += i__1) {
/* Computing MIN */
	    i__2 = nb, i__3 = *n - j + 1;
	    jb = MIN(i__2,i__3);

/*           Copy current block column of L to WORK and replace with */
/*           zeros. */

	    i__2 = j + jb - 1;
	    for (jj = j; jj <= i__2; ++jj) {
		i__3 = *n;
		for (i__ = jj + 1; i__ <= i__3; ++i__) {
		    work[i__ + (jj - j) * ldwork] = a[i__ + jj * a_dim1];
		    a[i__ + jj * a_dim1] = 0.;
/* L30: */
		}
/* L40: */
	    }

/*           Compute current block column of inv(A). */

	    if (j + jb <= *n) {
		i__2 = *n - j - jb + 1;
		dgemm_("No transpose", "No transpose", n, &jb, &i__2, &c_b20, 
			&a[(j + jb) * a_dim1 + 1], lda, &work[j + jb], &
			ldwork, &c_b22, &a[j * a_dim1 + 1], lda);
	    }
	    dtrsm_("Right", "Lower", "No transpose", "Unit", n, &jb, &c_b22, &
		    work[j], &ldwork, &a[j * a_dim1 + 1], lda);
/* L50: */
	}
    }

/*     Apply column interchanges. */

    for (j = *n - 1; j >= 1; --j) {
	jp = ipiv[j];
	if (jp != j) {
	    dswap_(n, &a[j * a_dim1 + 1], &c__1, &a[jp * a_dim1 + 1], &c__1);
	}
/* L60: */
    }

    work[1] = (double) iws;
    return 0;

/*     End of DGETRI */

} /* dgetri_ */
