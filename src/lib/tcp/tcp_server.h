#ifndef tcp_server_h__
#define tcp_server_h__

int signals_handler(int signal_number);
int init_server(int port);
void start_server(int port);
 
#endif  // tcp_server_h__

