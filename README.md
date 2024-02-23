# system_call_audit
This is a script for checking and logging system calls to the selected process in Linux.
# Installing
Compile main.cpp file </br>
`g++ main.cpp -o audit`
# Usage
Open your terminal and write this command </br>
`sudo ./audit <PID>`
# Tests
You can test this program using the file test.cpp to do this, type the following commands into the console: </br>
`g++ test.cpp -o test` </br>
`./test` </br>
Then get a PID of test proccess: </br>
`pidof test` </br>
Open new window in your terminal and type this command: </br>
`sudo ./audit <PID>` </br>
Back to previous window and type this command: </br>
`create` </br>
`quit` </br>
Change window and you will see your logs. Also you can see logs of your proccess in audit.log file.

