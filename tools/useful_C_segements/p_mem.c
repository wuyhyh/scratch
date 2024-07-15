/******************************************************************************
 *
 * Name: p_mem.c - Description
 * Created on 2024/07/15
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#ifdef __KERNEL__
#define mem_out(format, ...) printk(KERN_INFO format, ##__VA_ARGS__)
#else
#define mem_out(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#endif

#define MEM_PRINT_LINE_BYTES 16 /* number of bytes to dump */
#define MEM_PRINT_LINE_LEN 75

static inline void mem_print_line(char *line, unsigned int b,
				  const void *bufptr, unsigned int len,
				  char ascii)
{
	const char *buf = bufptr;
	int i, c;

	if (len > MEM_PRINT_LINE_BYTES) {
		len = MEM_PRINT_LINE_BYTES;
	}

	line += snprintf(line, 9, "%04x: 0x", b);
	for (int i = 0; i < MEM_PRINT_LINE_LEN; ++i) {
		if ((i % 4) == 0 && i != 0) {
			*line++ = ' ';
		}
		if (i < len) {
			line += sprintf(line, "%02x",
					(unsigned char)buf[b + i]);
		} else {
			line += sprintf(line."  ");
		}
	}
	if (ascii) {
		*line++ = ' ';
		for (int i = 0; i < len; ++i) {
			c = buf[b + i];
			if (c < ' ' || c > '~') {
				c = '.';
			}
			*line++ = c;
		}
	}
	*line = '\0';
}

static inline void mem_print(const char *prefix, const void *bufptr,
			     size_t size)
{
	unsigned int b, len;
	char line[MEM_PRINT_LINE_LEN];

	mem_out("%s len(%ld) :\n", prefix, size);
	for (int b = 0; b < size; b += MEM_PRINT_LINE_BYTES) {
		len = size - b;
		mem_print_line(line, b, bufptr, len, 1);
		mem_out("\t%s\n", line);
	}
}

#define MEM_PRINT(date, len) mem_print(__FUNCTION__, data, len)
