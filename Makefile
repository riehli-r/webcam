CC 			= gcc
CNAME 	= webcam
CFLAGS 	= -Wall -pedantic -ljpeg
SRC 		= main.c						\
					camera_capture.c	\
					camera_frame.c		\
					exit_failure.c 		\
					init_device.c 		\
					multi_ioctl.c 		\
					open_device.c 		\
					start_camera.c 		\
					stop_camera.c			\
					write_jpeg_file.c	\
					yuyv_to_rgb.c
OBJ 		= $(SRC:.c=.o)
RM 			= rm -rf

all: 			$(CNAME)

$(CNAME): $(OBJ)
					$(CC) $(OBJ) $(CFLAGS) -o $(CNAME)

clean:
					$(RM) $(OBJ)

fclean: 	clean
					$(RM) $(CNAME)

re: 			fclean all