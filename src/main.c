#include "campi/webcam.h"

int                     main(int argc, char **argv) {

  pthread_t             thread;
  t_camera              *camera;
  char                  *device;
  SOCKET                sock;
  SOCKADDR_IN           sin;
  int                   ret;

  if (argc < 3)
    device = "/dev/video1";
  else
    device = argv[2];

  sin = get_server_ip();
  STEP("Create TCP socket");
  sin.sin_port = htons(STREAM_PORT);
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == INVALID_SOCKET)
    exit_failure("INVALID_SOCKET");
  VALIDATE();

  STEP("Connection to the server");
  ret = connect(sock, (SOCKADDR*)&sin, sizeof(sin));
  if (ret == SOCKET_ERROR)
    exit_failure("connect");
  VALIDATE();

  camera = open_device(device, WIDTH, HEIGHT);
  camera->sock = &sock;
  get_infos(sock, camera);
  init_device(camera);
  start_camera(camera);

  if(pthread_create(&thread, NULL, listen_thread, camera) == -1)
    exit_failure("pthread_create");

  camera_loop(camera);

  if (pthread_join(thread, NULL))
    exit_failure("pthread_join");

  close(sock);
  stop_camera(camera);
  return (0);
}
