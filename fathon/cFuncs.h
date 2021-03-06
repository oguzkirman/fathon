//    cFuncs.h - array and mathematical operations C functions of fathon package
//    Copyright (C) 2019  Stefano Bianchi
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_multifit.h>

//polynomial fit
void polynomialFit(int obs, int degree, double *dx, double *dy, double *store)
{
    gsl_multifit_linear_workspace *ws;
    gsl_matrix *cov, *X;
    gsl_vector *y, *c;
    double chisq;
    int i, j;

    X = gsl_matrix_alloc(obs, degree);
    y = gsl_vector_alloc(obs);
    c = gsl_vector_alloc(degree);
    cov = gsl_matrix_alloc(degree, degree);
     
    for(i = 0; i < obs; i++){
        for(j = 0; j < degree; j++){
            gsl_matrix_set(X, i, j, pow(dx[i], j));
        }
        gsl_vector_set(y, i, dy[i]);
    }

    ws = gsl_multifit_linear_alloc(obs, degree);
    gsl_multifit_linear(X, y, c, cov, &chisq, ws);

    for(i = 0; i < degree; i++){
        store[i] = gsl_vector_get(c, i);
    }

    gsl_multifit_linear_free(ws);
    gsl_matrix_free(X);
    gsl_matrix_free(cov);
    gsl_vector_free(y);
    gsl_vector_free(c);
}

//range of double values
void double_range(double *vec, int L, double start, double step)
{
    int i;
    
    for(i = 0; i < L; i++){
        vec[i] = (double)(i * step + start);
    }
}

//creates a vector that is a portion of a bigger vector
void slice_vec(double *all_vec, double *sliced_vec, int start, int end)
{
    int i;
    
    for(i = 0; i <= (end - start); i++){
        sliced_vec[i] = all_vec[start+i];
    }
}

//mean of a vector
double mean(double *vec, int L)
{
    double avg = 0.0;
    int i;
    
    for(i = 0; i < L; i++){
        avg += vec[i];
    }
    avg /= (double)L;
    
    return avg;
}
