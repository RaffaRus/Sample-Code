#ifndef __Matrix4__
#define __Matrix4__

#include <Defines.h>
#include <ZAssert.h>
#include <Array.h>
#include <Bool.h>
#include <Math_obj.h>
#include <Math_defines.h>
#include <Std_cc_stream.h>
#include <Matrix3.h>

Z_START_NAMESPACE;

class DMATRIX;
class SMATRIX;
class MATRIX;
class MATRIX3;
class TENSOR1;
class TENSOR2;
class TENSOR3;
class TENSOR4;

ZCLASS MATRIX4 : public MATH_OBJECT {
       friend class VECTOR;
       friend class TENSOR2;
       friend class DMATRIX;
       friend class SMATRIX;
       friend class MATRIX;
       friend class MATRIX3;

  protected :

       int      _m;        
       int      _n;       
       int      _l;       
       int      _p;       

       double   ****mat;

       void init_ptr();
       void remove_ptr();

   public:

      const   int&     m;  // number of rows
      const   int&     n;  // number of columns
      const   int&     l;  // number of columns
      const   int&     p;  // number of columns

      MATRIX4();

      MATRIX4(int mm, int nn, int ll, int pp);

      ~MATRIX4();

      double&  operator()(int i, int j, int k, int h);
      const   double&  operator()(int i, int j, int k, int h) const;
      MATRIX4& operator=(const MATRIX4&);
      MATRIX4& operator=(const double&);
      friend WIN_THINGIE ZOSTREAM& operator<<(ZOSTREAM&,const MATRIX4&);
      friend WIN_THINGIE MATRIX4 operator*(const MATRIX&, const MATRIX4&);
};

//============================================================================  
// INLINES 
//============================================================================  

//inline MATRIX4::MATRIX4() : MATH_OBJECT(0), _n(0), _m(0), _l(0), mat(NULL), n(_n), m(_m), l(_l) { }

inline MATRIX4::MATRIX4(int mm, int nn, int ll, int pp) : MATH_OBJECT(0), _m(mm), _n(nn), _l(ll), _p(pp), m(_m), n(_n), l(_l), p(_p) { 
         init_ptr();
         #ifdef ZCHECK
            *this = DBL_MAX;
         #endif
}


inline double& MATRIX4::operator()(int i, int j, int k, int h)
{ 
//     #ifdef ZCHECK
//     assert(i>=0 && i<n && j>=0 && j<m && k>=0 && k<l);
//     assert(mat && mat[MAT_CHECK]);
//     #endif
//
//     #ifdef MATRIX_ALIGN_AS_FORTRAN
//          return mat[h][k][j][i];
//     #else
          return mat[i][j][k][h]; 
//     #endif
}
   
inline const double& MATRIX4::operator()(int i, int j, int k, int h)const
{ 
//     #ifdef ZCHECK
//     assert(i>=0 && i<n && j>=0 && j<m && k>=0 && k<l);
//     assert(mat && mat[MAT_CHECK]);
//     #endif
//     #ifdef MATRIX_ALIGN_AS_FORTRAN
//          return mat[k][j][i]; 
//     #else
          return mat[i][j][k][h]; 
//     #endif
}
//
//#undef MAT_CHECK

inline MATRIX4& MATRIX4::operator=(const MATRIX4& a)
{
    assert(a.m==m && a.n==n && a.l==l && a.p==p); 
    for(int ii=0;ii<a.m;ii++){
      for(int jj=0;jj<a.n;jj++){
        for(int kk=0;kk<a.l;kk++){
          for(int hh=0;hh<a.p;hh++){
            mat[ii][jj][kk][hh] = a.mat[ii][jj][kk][hh];
          } 
        }
      }
    }
    return *this;
}

inline MATRIX4& MATRIX4::operator=(const double& a)
{
    for(int ii=0;ii<m;ii++){
      for(int jj=0;jj<n;jj++){
        for(int kk=0;kk<l;kk++){
          for(int hh=0;hh<p;hh++){
            mat[ii][jj][kk][hh] = a;
          }
        }
      }
    }
    return *this;
}

Z_END_NAMESPACE;
#endif
