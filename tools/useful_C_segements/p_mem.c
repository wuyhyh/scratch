/******************************************************************************
 *
 * Name: p_mem.c - Description
 * Created on 2024/07/15
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#ifdef __KERNEL__
/* Use printk for output if in kernel space */
#define rmem_out(format, ...) printk(KERN_INFO format, ##__VA_ARGS__)
#else
/* Use fprintf for output to stdout if in user space */
#define rmem_out(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#endif

#define MEM_PRINT_LINE_BYTES 16 /* Number of bytes to dump per line */
#define MEM_PRINT_LINE_LEN 75 /* Maximum length of a line */

static inline void mem_print_line(char *line, unsigned int b,
				  const void *bufptr, unsigned int len,
				  char ascii)
{
	/* Cast the buffer pointer to a char pointer */
	const char *buf = bufptr;
	int c;

	/* Ensure len does not exceed bytes per line */
	if (len > MEM_PRINT_LINE_BYTES) {
		len = MEM_PRINT_LINE_BYTES;
	}

	/* Print the starting address of the line */
	line += snprintf(line, 9, "%04x: 0x", b);

	for (int i = 0; i < MEM_PRINT_LINE_BYTES; ++i) {
		if ((i % 4) == 0 && i != 0) {
			*line++ = ' '; /* Add a space every four bytes */
		}
		if (i < len) {
			/* Print buffer content in hex format */
			line += sprintf(line, "%02x",
					(unsigned char)buf[b + i]);
		} else {
			/* Print two spaces if beyond actual length */
			line += sprintf(line, "  ");
		}
	}

	if (ascii) {
		*line++ = ' ';
		for (int i = 0; i < len; ++i) {
			c = buf[b + i];
			if (c < ' ' || c > '~') {
				/* Replace non-printable characters with '.' */
				c = '.';
			}
			*line++ = c; /* Print ASCII characters */
		}
	}
	*line = '\0'; /* Terminate the string */
}

static inline void mem_print(const char *prefix, const void *bufptr,
			     size_t size)
{
	unsigned int b, len;
	char line[MEM_PRINT_LINE_LEN];
	/* Print the prefix and buffer length */
	rmem_out("%s len(%ld) :\n", prefix, size);

	for (b = 0; b < size; b += MEM_PRINT_LINE_BYTES) {
		len = size - b;
		/* Print each line of the buffer */
		mem_print_line(line, b, bufptr, len, 1);
		rmem_out("\t%s\n", line);
	}
}

/* Macro to print memory data with the current function name as prefix */
#define MEM_PRINT(data, len) mem_print(__FUNCTION__, data, len)