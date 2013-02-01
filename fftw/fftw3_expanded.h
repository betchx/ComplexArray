

// Constants

enum fftw_r2r_kind_do_not_use_me {
     FFTW_R2HC=0, FFTW_HC2R=1, FFTW_DHT=2,
     FFTW_REDFT00=3, FFTW_REDFT01=4, FFTW_REDFT10=5, FFTW_REDFT11=6,
     FFTW_RODFT00=7, FFTW_RODFT01=8, FFTW_RODFT10=9, FFTW_RODFT11=10
};

struct fftw_iodim_do_not_use_me {
     int n;                     
     int is;			
     int os;			
};

#define FFTW_FORWARD (-1)
#define FFTW_BACKWARD (+1)
/* documented flags */
#define FFTW_MEASURE (0U)
#define FFTW_DESTROY_INPUT (1U << 0)
#define FFTW_UNALIGNED (1U << 1)
#define FFTW_CONSERVE_MEMORY (1U << 2)
#define FFTW_EXHAUSTIVE (1U << 3) /* NO_EXHAUSTIVE is default */
#define FFTW_PRESERVE_INPUT (1U << 4) /* cancels FFTW_DESTROY_INPUT */
#define FFTW_PATIENT (1U << 5) /* IMPATIENT is default */
#define FFTW_ESTIMATE (1U << 6)
#define FFTW_WISDOM_ONLY (1U << 21)



// Double
 typedef double fftw_complex[2];
 typedef struct fftw_plan_s *fftw_plan;
 typedef struct fftw_iodim_do_not_use_me fftw_iodim;
 typedef struct fftw_iodim64_do_not_use_me fftw_iodim64;
 typedef enum fftw_r2r_kind_do_not_use_me fftw_r2r_kind;
 typedef fftw_write_char_func_do_not_use_me fftw_write_char_func;
 typedef fftw_read_char_func_do_not_use_me fftw_read_char_func;
 extern __declspec(dllimport) void fftw_execute(const fftw_plan p);
 extern __declspec(dllimport) fftw_plan fftw_plan_dft(int rank, const int *n, fftw_complex *in, fftw_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_dft_1d(int n, fftw_complex *in, fftw_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_dft_2d(int n0, int n1, fftw_complex *in, fftw_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_dft_3d(int n0, int n1, int n2, fftw_complex *in, fftw_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_many_dft(int rank, const int *n, int howmany, fftw_complex *in, const int *inembed, int istride, int idist, fftw_complex *out, const int *onembed, int ostride, int odist, int sign, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_guru_dft(int rank, const fftw_iodim *dims, int howmany_rank, const fftw_iodim *howmany_dims, fftw_complex *in, fftw_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_guru_split_dft(int rank, const fftw_iodim *dims, int howmany_rank, const fftw_iodim *howmany_dims, double *ri, double *ii, double *ro, double *io, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_guru64_dft(int rank, const fftw_iodim64 *dims, int howmany_rank, const fftw_iodim64 *howmany_dims, fftw_complex *in, fftw_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_guru64_split_dft(int rank, const fftw_iodim64 *dims, int howmany_rank, const fftw_iodim64 *howmany_dims, double *ri, double *ii, double *ro, double *io, unsigned flags);
 extern __declspec(dllimport) void fftw_execute_dft(const fftw_plan p, fftw_complex *in, fftw_complex *out);
 extern __declspec(dllimport) void fftw_execute_split_dft(const fftw_plan p, double *ri, double *ii, double *ro, double *io);
 extern __declspec(dllimport) fftw_plan fftw_plan_many_dft_r2c(int rank, const int *n, int howmany, double *in, const int *inembed, int istride, int idist, fftw_complex *out, const int *onembed, int ostride, int odist, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_dft_r2c(int rank, const int *n, double *in, fftw_complex *out, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_dft_r2c_1d(int n,double *in,fftw_complex *out,unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_dft_r2c_2d(int n0, int n1, double *in, fftw_complex *out, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_dft_r2c_3d(int n0, int n1, int n2, double *in, fftw_complex *out, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_many_dft_c2r(int rank, const int *n, int howmany, fftw_complex *in, const int *inembed, int istride, int idist, double *out, const int *onembed, int ostride, int odist, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_dft_c2r(int rank, const int *n, fftw_complex *in, double *out, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_dft_c2r_1d(int n,fftw_complex *in,double *out,unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_dft_c2r_2d(int n0, int n1, fftw_complex *in, double *out, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_dft_c2r_3d(int n0, int n1, int n2, fftw_complex *in, double *out, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_guru_dft_r2c(int rank, const fftw_iodim *dims, int howmany_rank, const fftw_iodim *howmany_dims, double *in, fftw_complex *out, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_guru_dft_c2r(int rank, const fftw_iodim *dims, int howmany_rank, const fftw_iodim *howmany_dims, fftw_complex *in, double *out, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_guru_split_dft_r2c( int rank, const fftw_iodim *dims, int howmany_rank, const fftw_iodim *howmany_dims, double *in, double *ro, double *io, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_guru_split_dft_c2r( int rank, const fftw_iodim *dims, int howmany_rank, const fftw_iodim *howmany_dims, double *ri, double *ii, double *out, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_guru64_dft_r2c(int rank, const fftw_iodim64 *dims, int howmany_rank, const fftw_iodim64 *howmany_dims, double *in, fftw_complex *out, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_guru64_dft_c2r(int rank, const fftw_iodim64 *dims, int howmany_rank, const fftw_iodim64 *howmany_dims, fftw_complex *in, double *out, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_guru64_split_dft_r2c( int rank, const fftw_iodim64 *dims, int howmany_rank, const fftw_iodim64 *howmany_dims, double *in, double *ro, double *io, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_guru64_split_dft_c2r( int rank, const fftw_iodim64 *dims, int howmany_rank, const fftw_iodim64 *howmany_dims, double *ri, double *ii, double *out, unsigned flags);
 extern __declspec(dllimport) void fftw_execute_dft_r2c(const fftw_plan p, double *in, fftw_complex *out);
 extern __declspec(dllimport) void fftw_execute_dft_c2r(const fftw_plan p, fftw_complex *in, double *out);
 extern __declspec(dllimport) void fftw_execute_split_dft_r2c(const fftw_plan p, double *in, double *ro, double *io);
 extern __declspec(dllimport) void fftw_execute_split_dft_c2r(const fftw_plan p, double *ri, double *ii, double *out);
 extern __declspec(dllimport) fftw_plan fftw_plan_many_r2r(int rank, const int *n, int howmany, double *in, const int *inembed, int istride, int idist, double *out, const int *onembed, int ostride, int odist, const fftw_r2r_kind *kind, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_r2r(int rank, const int *n, double *in, double *out, const fftw_r2r_kind *kind, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_r2r_1d(int n, double *in, double *out, fftw_r2r_kind kind, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_r2r_2d(int n0, int n1, double *in, double *out, fftw_r2r_kind kind0, fftw_r2r_kind kind1, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_r2r_3d(int n0, int n1, int n2, double *in, double *out, fftw_r2r_kind kind0, fftw_r2r_kind kind1, fftw_r2r_kind kind2, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_guru_r2r(int rank, const fftw_iodim *dims, int howmany_rank, const fftw_iodim *howmany_dims, double *in, double *out, const fftw_r2r_kind *kind, unsigned flags);
 extern __declspec(dllimport) fftw_plan fftw_plan_guru64_r2r(int rank, const fftw_iodim64 *dims, int howmany_rank, const fftw_iodim64 *howmany_dims, double *in, double *out, const fftw_r2r_kind *kind, unsigned flags);
 extern __declspec(dllimport) void fftw_execute_r2r(const fftw_plan p, double *in, double *out);
 extern __declspec(dllimport) void fftw_destroy_plan(fftw_plan p);
 extern __declspec(dllimport) void fftw_forget_wisdom(void);
 extern __declspec(dllimport) void fftw_cleanup(void);
 extern __declspec(dllimport) void fftw_set_timelimit(double t);
 extern __declspec(dllimport) void fftw_plan_with_nthreads(int nthreads);
 extern __declspec(dllimport) int fftw_init_threads(void);
 extern __declspec(dllimport) void fftw_cleanup_threads(void);
 extern __declspec(dllimport) int fftw_export_wisdom_to_filename(const char *filename);
 extern __declspec(dllimport) void fftw_export_wisdom_to_file(FILE *output_file);
 extern __declspec(dllimport) char *fftw_export_wisdom_to_string(void);
 extern __declspec(dllimport) void fftw_export_wisdom(fftw_write_char_func write_char, void *data);
 extern __declspec(dllimport) int fftw_import_system_wisdom(void);
 extern __declspec(dllimport) int fftw_import_wisdom_from_filename(const char *filename);
 extern __declspec(dllimport) int fftw_import_wisdom_from_file(FILE *input_file);
 extern __declspec(dllimport) int fftw_import_wisdom_from_string(const char *input_string);
 extern __declspec(dllimport) int fftw_import_wisdom(fftw_read_char_func read_char, void *data);
 extern __declspec(dllimport) void fftw_fprint_plan(const fftw_plan p, FILE *output_file);
 extern __declspec(dllimport) void fftw_print_plan(const fftw_plan p);
 extern __declspec(dllimport) void *fftw_malloc(size_t n);
 extern __declspec(dllimport) double *fftw_alloc_real(size_t n);
 extern __declspec(dllimport) fftw_complex *fftw_alloc_complex(size_t n);
 extern __declspec(dllimport) void fftw_free(void *p);
 extern __declspec(dllimport) void fftw_flops(const fftw_plan p, double *add, double *mul, double *fmas);
 extern __declspec(dllimport) double fftw_estimate_cost(const fftw_plan p);
 extern __declspec(dllimport) double fftw_cost(const fftw_plan p);
 extern __declspec(dllimport) const char fftw_version[];
 extern __declspec(dllimport) const char fftw_cc[];
 extern __declspec(dllimport) const char fftw_codelet_optim[];

 // Float
typedef float fftwf_complex[2];
 typedef struct fftwf_plan_s *fftwf_plan;
 typedef struct fftw_iodim_do_not_use_me fftwf_iodim;
 typedef struct fftw_iodim64_do_not_use_me fftwf_iodim64;
 typedef enum fftw_r2r_kind_do_not_use_me fftwf_r2r_kind;
 typedef fftw_write_char_func_do_not_use_me fftwf_write_char_func;
 typedef fftw_read_char_func_do_not_use_me fftwf_read_char_func;
 extern __declspec(dllimport) void fftwf_execute(const fftwf_plan p);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_dft(int rank, const int *n, fftwf_complex *in, fftwf_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_dft_1d(int n, fftwf_complex *in, fftwf_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_dft_2d(int n0, int n1, fftwf_complex *in, fftwf_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_dft_3d(int n0, int n1, int n2, fftwf_complex *in, fftwf_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_many_dft(int rank, const int *n, int howmany, fftwf_complex *in, const int *inembed, int istride, int idist, fftwf_complex *out, const int *onembed, int ostride, int odist, int sign, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_guru_dft(int rank, const fftwf_iodim *dims, int howmany_rank, const fftwf_iodim *howmany_dims, fftwf_complex *in, fftwf_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_guru_split_dft(int rank, const fftwf_iodim *dims, int howmany_rank, const fftwf_iodim *howmany_dims, float *ri, float *ii, float *ro, float *io, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_guru64_dft(int rank, const fftwf_iodim64 *dims, int howmany_rank, const fftwf_iodim64 *howmany_dims, fftwf_complex *in, fftwf_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_guru64_split_dft(int rank, const fftwf_iodim64 *dims, int howmany_rank, const fftwf_iodim64 *howmany_dims, float *ri, float *ii, float *ro, float *io, unsigned flags);
 extern __declspec(dllimport) void fftwf_execute_dft(const fftwf_plan p, fftwf_complex *in, fftwf_complex *out);
 extern __declspec(dllimport) void fftwf_execute_split_dft(const fftwf_plan p, float *ri, float *ii, float *ro, float *io);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_many_dft_r2c(int rank, const int *n, int howmany, float *in, const int *inembed, int istride, int idist, fftwf_complex *out, const int *onembed, int ostride, int odist, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_dft_r2c(int rank, const int *n, float *in, fftwf_complex *out, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_dft_r2c_1d(int n,float *in,fftwf_complex *out,unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_dft_r2c_2d(int n0, int n1, float *in, fftwf_complex *out, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_dft_r2c_3d(int n0, int n1, int n2, float *in, fftwf_complex *out, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_many_dft_c2r(int rank, const int *n, int howmany, fftwf_complex *in, const int *inembed, int istride, int idist, float *out, const int *onembed, int ostride, int odist, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_dft_c2r(int rank, const int *n, fftwf_complex *in, float *out, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_dft_c2r_1d(int n,fftwf_complex *in,float *out,unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_dft_c2r_2d(int n0, int n1, fftwf_complex *in, float *out, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_dft_c2r_3d(int n0, int n1, int n2, fftwf_complex *in, float *out, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_guru_dft_r2c(int rank, const fftwf_iodim *dims, int howmany_rank, const fftwf_iodim *howmany_dims, float *in, fftwf_complex *out, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_guru_dft_c2r(int rank, const fftwf_iodim *dims, int howmany_rank, const fftwf_iodim *howmany_dims, fftwf_complex *in, float *out, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_guru_split_dft_r2c( int rank, const fftwf_iodim *dims, int howmany_rank, const fftwf_iodim *howmany_dims, float *in, float *ro, float *io, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_guru_split_dft_c2r( int rank, const fftwf_iodim *dims, int howmany_rank, const fftwf_iodim *howmany_dims, float *ri, float *ii, float *out, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_guru64_dft_r2c(int rank, const fftwf_iodim64 *dims, int howmany_rank, const fftwf_iodim64 *howmany_dims, float *in, fftwf_complex *out, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_guru64_dft_c2r(int rank, const fftwf_iodim64 *dims, int howmany_rank, const fftwf_iodim64 *howmany_dims, fftwf_complex *in, float *out, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_guru64_split_dft_r2c( int rank, const fftwf_iodim64 *dims, int howmany_rank, const fftwf_iodim64 *howmany_dims, float *in, float *ro, float *io, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_guru64_split_dft_c2r( int rank, const fftwf_iodim64 *dims, int howmany_rank, const fftwf_iodim64 *howmany_dims, float *ri, float *ii, float *out, unsigned flags);
 extern __declspec(dllimport) void fftwf_execute_dft_r2c(const fftwf_plan p, float *in, fftwf_complex *out);
 extern __declspec(dllimport) void fftwf_execute_dft_c2r(const fftwf_plan p, fftwf_complex *in, float *out);
 extern __declspec(dllimport) void fftwf_execute_split_dft_r2c(const fftwf_plan p, float *in, float *ro, float *io);
 extern __declspec(dllimport) void fftwf_execute_split_dft_c2r(const fftwf_plan p, float *ri, float *ii, float *out);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_many_r2r(int rank, const int *n, int howmany, float *in, const int *inembed, int istride, int idist, float *out, const int *onembed, int ostride, int odist, const fftwf_r2r_kind *kind, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_r2r(int rank, const int *n, float *in, float *out, const fftwf_r2r_kind *kind, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_r2r_1d(int n, float *in, float *out, fftwf_r2r_kind kind, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_r2r_2d(int n0, int n1, float *in, float *out, fftwf_r2r_kind kind0, fftwf_r2r_kind kind1, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_r2r_3d(int n0, int n1, int n2, float *in, float *out, fftwf_r2r_kind kind0, fftwf_r2r_kind kind1, fftwf_r2r_kind kind2, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_guru_r2r(int rank, const fftwf_iodim *dims, int howmany_rank, const fftwf_iodim *howmany_dims, float *in, float *out, const fftwf_r2r_kind *kind, unsigned flags);
 extern __declspec(dllimport) fftwf_plan fftwf_plan_guru64_r2r(int rank, const fftwf_iodim64 *dims, int howmany_rank, const fftwf_iodim64 *howmany_dims, float *in, float *out, const fftwf_r2r_kind *kind, unsigned flags);
 extern __declspec(dllimport) void fftwf_execute_r2r(const fftwf_plan p, float *in, float *out);
 extern __declspec(dllimport) void fftwf_destroy_plan(fftwf_plan p);
 extern __declspec(dllimport) void fftwf_forget_wisdom(void);
 extern __declspec(dllimport) void fftwf_cleanup(void);
 extern __declspec(dllimport) void fftwf_set_timelimit(double t);
 extern __declspec(dllimport) void fftwf_plan_with_nthreads(int nthreads);
 extern __declspec(dllimport) int fftwf_init_threads(void);
 extern __declspec(dllimport) void fftwf_cleanup_threads(void);
 extern __declspec(dllimport) int fftwf_export_wisdom_to_filename(const char *filename);
 extern __declspec(dllimport) void fftwf_export_wisdom_to_file(FILE *output_file);
 extern __declspec(dllimport) char *fftwf_export_wisdom_to_string(void);
 extern __declspec(dllimport) void fftwf_export_wisdom(fftwf_write_char_func write_char, void *data);
 extern __declspec(dllimport) int fftwf_import_system_wisdom(void);
 extern __declspec(dllimport) int fftwf_import_wisdom_from_filename(const char *filename);
 extern __declspec(dllimport) int fftwf_import_wisdom_from_file(FILE *input_file);
 extern __declspec(dllimport) int fftwf_import_wisdom_from_string(const char *input_string);
 extern __declspec(dllimport) int fftwf_import_wisdom(fftwf_read_char_func read_char, void *data);
 extern __declspec(dllimport) void fftwf_fprint_plan(const fftwf_plan p, FILE *output_file);
 extern __declspec(dllimport) void fftwf_print_plan(const fftwf_plan p);
 extern __declspec(dllimport) void *fftwf_malloc(size_t n);
 extern __declspec(dllimport) float *fftwf_alloc_real(size_t n);
 extern __declspec(dllimport) fftwf_complex *fftwf_alloc_complex(size_t n);
 extern __declspec(dllimport) void fftwf_free(void *p);
 extern __declspec(dllimport) void fftwf_flops(const fftwf_plan p, double *add, double *mul, double *fmas);
 extern __declspec(dllimport) double fftwf_estimate_cost(const fftwf_plan p);
 extern __declspec(dllimport) double fftwf_cost(const fftwf_plan p);
 extern __declspec(dllimport) const char fftwf_version[];
 extern __declspec(dllimport) const char fftwf_cc[];
 extern __declspec(dllimport) const char fftwf_codelet_optim[];


 // Long Double

typedef long double fftwl_complex[2];
 typedef struct fftwl_plan_s *fftwl_plan;
 typedef struct fftw_iodim_do_not_use_me fftwl_iodim;
 typedef struct fftw_iodim64_do_not_use_me fftwl_iodim64;
 typedef enum fftw_r2r_kind_do_not_use_me fftwl_r2r_kind;
 typedef fftw_write_char_func_do_not_use_me fftwl_write_char_func;
 typedef fftw_read_char_func_do_not_use_me fftwl_read_char_func;
 extern __declspec(dllimport) void fftwl_execute(const fftwl_plan p);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_dft(int rank, const int *n, fftwl_complex *in, fftwl_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_dft_1d(int n, fftwl_complex *in, fftwl_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_dft_2d(int n0, int n1, fftwl_complex *in, fftwl_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_dft_3d(int n0, int n1, int n2, fftwl_complex *in, fftwl_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_many_dft(int rank, const int *n, int howmany, fftwl_complex *in, const int *inembed, int istride, int idist, fftwl_complex *out, const int *onembed, int ostride, int odist, int sign, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_guru_dft(int rank, const fftwl_iodim *dims, int howmany_rank, const fftwl_iodim *howmany_dims, fftwl_complex *in, fftwl_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_guru_split_dft(int rank, const fftwl_iodim *dims, int howmany_rank, const fftwl_iodim *howmany_dims, long double *ri, long double *ii, long double *ro, long double *io, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_guru64_dft(int rank, const fftwl_iodim64 *dims, int howmany_rank, const fftwl_iodim64 *howmany_dims, fftwl_complex *in, fftwl_complex *out, int sign, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_guru64_split_dft(int rank, const fftwl_iodim64 *dims, int howmany_rank, const fftwl_iodim64 *howmany_dims, long double *ri, long double *ii, long double *ro, long double *io, unsigned flags);
 extern __declspec(dllimport) void fftwl_execute_dft(const fftwl_plan p, fftwl_complex *in, fftwl_complex *out);
 extern __declspec(dllimport) void fftwl_execute_split_dft(const fftwl_plan p, long double *ri, long double *ii, long double *ro, long double *io);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_many_dft_r2c(int rank, const int *n, int howmany, long double *in, const int *inembed, int istride, int idist, fftwl_complex *out, const int *onembed, int ostride, int odist, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_dft_r2c(int rank, const int *n, long double *in, fftwl_complex *out, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_dft_r2c_1d(int n,long double *in,fftwl_complex *out,unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_dft_r2c_2d(int n0, int n1, long double *in, fftwl_complex *out, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_dft_r2c_3d(int n0, int n1, int n2, long double *in, fftwl_complex *out, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_many_dft_c2r(int rank, const int *n, int howmany, fftwl_complex *in, const int *inembed, int istride, int idist, long double *out, const int *onembed, int ostride, int odist, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_dft_c2r(int rank, const int *n, fftwl_complex *in, long double *out, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_dft_c2r_1d(int n,fftwl_complex *in,long double *out,unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_dft_c2r_2d(int n0, int n1, fftwl_complex *in, long double *out, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_dft_c2r_3d(int n0, int n1, int n2, fftwl_complex *in, long double *out, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_guru_dft_r2c(int rank, const fftwl_iodim *dims, int howmany_rank, const fftwl_iodim *howmany_dims, long double *in, fftwl_complex *out, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_guru_dft_c2r(int rank, const fftwl_iodim *dims, int howmany_rank, const fftwl_iodim *howmany_dims, fftwl_complex *in, long double *out, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_guru_split_dft_r2c( int rank, const fftwl_iodim *dims, int howmany_rank, const fftwl_iodim *howmany_dims, long double *in, long double *ro, long double *io, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_guru_split_dft_c2r( int rank, const fftwl_iodim *dims, int howmany_rank, const fftwl_iodim *howmany_dims, long double *ri, long double *ii, long double *out, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_guru64_dft_r2c(int rank, const fftwl_iodim64 *dims, int howmany_rank, const fftwl_iodim64 *howmany_dims, long double *in, fftwl_complex *out, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_guru64_dft_c2r(int rank, const fftwl_iodim64 *dims, int howmany_rank, const fftwl_iodim64 *howmany_dims, fftwl_complex *in, long double *out, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_guru64_split_dft_r2c( int rank, const fftwl_iodim64 *dims, int howmany_rank, const fftwl_iodim64 *howmany_dims, long double *in, long double *ro, long double *io, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_guru64_split_dft_c2r( int rank, const fftwl_iodim64 *dims, int howmany_rank, const fftwl_iodim64 *howmany_dims, long double *ri, long double *ii, long double *out, unsigned flags);
 extern __declspec(dllimport) void fftwl_execute_dft_r2c(const fftwl_plan p, long double *in, fftwl_complex *out);
 extern __declspec(dllimport) void fftwl_execute_dft_c2r(const fftwl_plan p, fftwl_complex *in, long double *out);
 extern __declspec(dllimport) void fftwl_execute_split_dft_r2c(const fftwl_plan p, long double *in, long double *ro, long double *io);
 extern __declspec(dllimport) void fftwl_execute_split_dft_c2r(const fftwl_plan p, long double *ri, long double *ii, long double *out);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_many_r2r(int rank, const int *n, int howmany, long double *in, const int *inembed, int istride, int idist, long double *out, const int *onembed, int ostride, int odist, const fftwl_r2r_kind *kind, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_r2r(int rank, const int *n, long double *in, long double *out, const fftwl_r2r_kind *kind, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_r2r_1d(int n, long double *in, long double *out, fftwl_r2r_kind kind, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_r2r_2d(int n0, int n1, long double *in, long double *out, fftwl_r2r_kind kind0, fftwl_r2r_kind kind1, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_r2r_3d(int n0, int n1, int n2, long double *in, long double *out, fftwl_r2r_kind kind0, fftwl_r2r_kind kind1, fftwl_r2r_kind kind2, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_guru_r2r(int rank, const fftwl_iodim *dims, int howmany_rank, const fftwl_iodim *howmany_dims, long double *in, long double *out, const fftwl_r2r_kind *kind, unsigned flags);
 extern __declspec(dllimport) fftwl_plan fftwl_plan_guru64_r2r(int rank, const fftwl_iodim64 *dims, int howmany_rank, const fftwl_iodim64 *howmany_dims, long double *in, long double *out, const fftwl_r2r_kind *kind, unsigned flags);
 extern __declspec(dllimport) void fftwl_execute_r2r(const fftwl_plan p, long double *in, long double *out);
 extern __declspec(dllimport) void fftwl_destroy_plan(fftwl_plan p);
 extern __declspec(dllimport) void fftwl_forget_wisdom(void);
 extern __declspec(dllimport) void fftwl_cleanup(void);
 extern __declspec(dllimport) void fftwl_set_timelimit(double t);
 extern __declspec(dllimport) void fftwl_plan_with_nthreads(int nthreads);
 extern __declspec(dllimport) int fftwl_init_threads(void);
 extern __declspec(dllimport) void fftwl_cleanup_threads(void);
 extern __declspec(dllimport) int fftwl_export_wisdom_to_filename(const char *filename);
 extern __declspec(dllimport) void fftwl_export_wisdom_to_file(FILE *output_file);
 extern __declspec(dllimport) char *fftwl_export_wisdom_to_string(void);
 extern __declspec(dllimport) void fftwl_export_wisdom(fftwl_write_char_func write_char, void *data);
 extern __declspec(dllimport) int fftwl_import_system_wisdom(void);
 extern __declspec(dllimport) int fftwl_import_wisdom_from_filename(const char *filename);
 extern __declspec(dllimport) int fftwl_import_wisdom_from_file(FILE *input_file);
 extern __declspec(dllimport) int fftwl_import_wisdom_from_string(const char *input_string);
 extern __declspec(dllimport) int fftwl_import_wisdom(fftwl_read_char_func read_char, void *data);
 extern __declspec(dllimport) void fftwl_fprint_plan(const fftwl_plan p, FILE *output_file);
 extern __declspec(dllimport) void fftwl_print_plan(const fftwl_plan p);
 extern __declspec(dllimport) void *fftwl_malloc(size_t n);
 extern __declspec(dllimport) long double *fftwl_alloc_real(size_t n);
 extern __declspec(dllimport) fftwl_complex *fftwl_alloc_complex(size_t n);
 extern __declspec(dllimport) void fftwl_free(void *p);
 extern __declspec(dllimport) void fftwl_flops(const fftwl_plan p, double *add, double *mul, double *fmas);
 extern __declspec(dllimport) double fftwl_estimate_cost(const fftwl_plan p);
 extern __declspec(dllimport) double fftwl_cost(const fftwl_plan p);
 extern __declspec(dllimport) const char fftwl_version[];
 extern __declspec(dllimport) const char fftwl_cc[];
 extern __declspec(dllimport) const char fftwl_codelet_optim[];

