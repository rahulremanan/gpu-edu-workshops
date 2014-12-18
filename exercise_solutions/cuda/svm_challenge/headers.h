
/* include the ATLAS headers */

extern "C"
{
#include <cblas.h>
}

/* choose precision to train and classify.  Only float and double are 
 * currently suppored
 */

typedef double floatType_t;

/* macro to convert 2d coords to 1d offset */

#define INDX(row,col,ld) (((col) * (ld)) + (row))

/* macros for max/min to combine with argmin */

#define MYMAX(val,array,i,index) \
if( array[i] > val ) \
{ \
  val = array[i]; \
  index = i; \
} \

#define MYMIN(val,array,i,index) \
if( array[i] < val ) \
{ \
  val = array[i]; \
  index = i; \
} \

/* macro to clip values from min to max */

#define CLIP(val,min,max) \
if( (val) < (min) ) val = (min); \
else if( (val) > (max) ) val = (max);

/* hardcoded constants for training and test set size and feature
 * vector size
 */

#define FEATURE_VECTOR_SIZE (1899)
#define TRAINING_SET_SIZE (4000)
#define TEST_SET_SIZE (1000)

#ifdef DEBUG
#define CUDA_CALL(F)  if( (F) != cudaSuccess ) \
  {printf("Error %s at %s:%d\n", cudaGetErrorString(cudaGetLastError()), \
   __FILE__,__LINE__); exit(-1);}
#define CUDA_CHECK()  if( (cudaPeekAtLastError()) != cudaSuccess ) \
  {printf("Error %s at %s:%d\n", cudaGetErrorString(cudaGetLastError()), \
   __FILE__,__LINE__-1); exit(-1);}
#else
#define CUDA_CALL(F) (F)
#define CUDA_CHECK()
#endif

/* function defs */

void readMatrixFromFile( char *, int *, const int, const int );

void calculateBI( floatType_t const *,
                  floatType_t const *,
                  floatType_t const *,
                  int ,
                  floatType_t *, floatType_t *,
                  int *, int * );

void svmTrain( floatType_t const *, floatType_t const *, floatType_t const,
               const int, const int,
               const floatType_t , const int,
               floatType_t * );

void svmPredict( floatType_t const *, floatType_t const *,  
                 int const, int const, int * );
