#include <Bool.h>

#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <memory.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <Std_cc_stream.h>

#include <Zminmax.h>
#include <Array.h>
#include <Error_messager.h>
#include <ZMath.h>
#include <Math_function.h>
#ifndef NOCLIENT
#include <Out_message.h>
#endif
#include <Print.h>
#include <Tool_debug.h>

#include <Tensor1.h>
#include <Tensor2.h>
#include <Tensor3.h>
#include <Tensor4.h>

#include <Aaa_zmat_globals.h>
#include <Matrix4.h>
#include <Matrix3.h>

Z_START_NAMESPACE;


void MATRIX4::init_ptr()
{
  int msize=_m*_n*_l*_p;
  if(msize) {
    mat = new double***[m];
    for(int ii=0;ii<m;ii++){
      mat[ii] = new double**[n];
      for(int jj=0;jj<n;jj++){
        mat[ii][jj] = new double*[l];
        for(int kk=0;kk<l;kk++){
          mat[ii][jj][kk] = new double[p];
        }
      }
    }
  } else
  ERROR("Not-initialized MATRIX4");
}

void MATRIX4::remove_ptr()
{
  if(mat!=NULL) {
    for(int ii=0;ii<m;ii++){
      for(int jj=0;jj<n;jj++){
        for(int kk=0;kk<l;kk++){
          delete[] mat[ii][jj][kk];
        }
        delete[] mat[ii][jj];
      }
      delete[] mat[ii];
    }
    delete[] mat;
  }
}

MATRIX4::~MATRIX4()
{
  if (if_is_sub()==FALSE) remove_ptr();
}

ostream& operator<<(ostream& ost,const MATRIX4& a)
{
  int i,j,k,h;

  for(i=0;i<a.m;i++){
    ost<<endl<<"i = "<<(i+1)<<"\n ";
    for(j=0;j<a.n;j++){
      ost<<endl<<"j = "<<(j+1)<<"\n [ ";
      for(k=0;k<a.l;k++) {
        for(h=0;h<a.p;h++) ost<<a(i,j,k,h)<<" ";
        if(k<a.l-1) ost<<endl;
        else ost<<" ] "<<endl;
      }
    }
  }
  ost<<endl<<flush;
  return ost;
}

MATRIX4 operator*(const MATRIX& a, const MATRIX4& b)
{
   assert(a.m==b.m);
   MATRIX4 c(b.l,b.m,b.n,b.p); c=0.;
   for(int ii=0;ii<a.n;ii++){
     for(int jj=0;jj<a.m;jj++){
       for(int kk=0;kk<b.n;kk++){
         for(int ll=0;ll<b.l;ll++){
           for(int mm=0;mm<b.p;mm++){ 
              c.mat[ii][jj][kk][ll]  = c.mat[ii][jj][kk][ll] + a(ii,jj)*b(jj,kk,ll,mm); // c_{ijlk} = a_{ij}b_{jklm}
           }
         }
       }
     }
   }
   return c;

}


Z_END_NAMESPACE;
