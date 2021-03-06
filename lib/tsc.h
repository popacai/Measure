/* V 0.1
 * tao comment:
 *  .h for TSC init and log
 *  lib for testing, so that we can use it in any where
 *  please implement functions in tsc.c
 *  Write a makefile to make .a and .so
 *  Write a makefile to install lib with the name tsc
 */

//change it if nessary
unsigned long get_tsc(void);
//return the diff
unsigned long diff_tsc(unsigned long t1, unsigned long t2); 

//tsc overhead
#define TEST_TSC_RAMPUP 10
#define TEST_TSC_LOOP 100000
unsigned long tsc_overhead;
unsigned long test_tsc_overhead(); // return the unsigned long


//record functions
unsigned long timestamp1;
unsigned long timestamp2;

inline int record_begin(void); // timestamp1 = get_tsc() return 0; 
inline int record_end(void);   // timestamp2 = get_tsc() return 0;
unsigned long get_result(); 
//return timestamp2 - timestamp1 - overhead of tsc;
