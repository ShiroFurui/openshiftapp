#include "mbed.h"
#include "EthernetNetIf.h"
#include "SimpleSocket.h"



  
char *response0 = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n\
    <META HTTP-EQUIV=\"Refresh\" CONTENT=\"1\">\
    <html><head><title>mbed web server</title></head>\
    <body><h2>Analog Input</h2><table cellpadding=\"5\">";
char *response1 = "<tr style=\"background:#ccccff\"><th>pin</th><th>value</th></tr>";
char *response2 = "<tr style=\"background:#cccccc\"><td>p%d</td><td align=\"center\">%f</td></tr>";
char *response3 = "</table></body></html>";

int main() {
    EthernetNetIf eth;
    eth.setup();
    ServerSocket server(80);
    while (true) {
        ClientSocket socket = server.accept();
        while (socket) {
            if (socket.available()) {
                while (socket.available())
                    socket.read();
                socket.printf(response0);
                socket.printf(response1);
                AnalogIn analogPin[] = {p15, p16, p17, p18, p19, p20};
                for (int i = 0; i < 6; i++) socket.printf(response2, 15 + i, analogPin[i].read());
                socket.printf(response3);
                socket.close();
            }
        }
    }
}