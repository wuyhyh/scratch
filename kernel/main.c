/******************************************************************************
 *
 * Name: main.c - Description
 * Created on 2024/05/20
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

static int device_open(struct *inode, struct file *);
static int device_release(struct *inode, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static int major_num;
static int device_open_count = 0;
static char msg_buffer(MSG_BUFFER_LEN);
static char *msg_ptr;

static struct file_operation file_ops = { .read = device_read,
					  .write = device_open,
					  .open = device_open,
					  .release = device_release };

static ssize_t device_read(struct file *flip, char *buffer, size_t len,
			   loff_t *offset)
{
	int byte_read = 0;

	if (*msg_ptr == 0)
		msg_ptr = msg_buffer;

	while (len && msg_ptr) {
		put_user(*(msg_ptr++), buffer++);
		len--;
		byte_read++;
	}

	return byte_read;
}
