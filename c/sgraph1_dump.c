
/* Dump an SG1 file to an OUT file.
 *
 * INVOCATION
 *
 *    $0 SG1-FILE OUT-FILE
 */

#include "width.ma.h"
#include "width.ua.h"
#include "width.va.h"
#include "width.wa.h"
#include "width.ta.h"

#include "sgraph1_io.a.h"

#include <stdio.h>

int main(int argc, char **argv)
{
	/* Not implemented yet */ 
	assert(TYPE_wa == '-' && TYPE_ta == '-');

	if (argc != 3) {
		fprintf(stderr, "*** wrong number of arguments/n");
		exit(1); 
	}

	const char *const filename_sg1= argv[1];
	const char *const filename_out= argv[2]; 

	FILE *out= fopen(filename_out, "w");
	if (out == NULL) {
		perror(filename_out);
		exit(1); 
	}

	struct sgraph1_reader_a r;

	if (0 > sgraph1_open_read_a(filename_sg1, &r, 2)) {
		exit(1); 
	}

	if (0 > sgraph1_advise_a(&r, MADV_SEQUENTIAL)) {
		perror(filename_sg1); 
		exit(1);
	}

	assert(r.h->format == FORMAT_SYM);

	for (ua_ft u= 0;  u < r.h->n1;  ++u) {

		ma_ft end= (u == r.h->n1 - 1) ? r.h->m : read_ma(r.adj_to, u + 1);
		for (ma_ft i= read_ma(r.adj_to, u);  i < end;  ++i) {
			va_ft v= read_va(r.to, i);
			fprintf(out, "%" PR_fua "\t%" PR_fva "\n", u + 1, v + 1); 
		}
	}

	if (0 > fclose(out)) {
		perror(filename_out);
		exit(1);
	}

	exit(0); 
}
