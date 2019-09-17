**** Readme file for assignment 9  *******

Design preemptive and non-preemptive SJF (Shortest Job First) CPU scheduler
You have to (1) compute various performance measures (turnaround time, 
waiting time, throughput)


The code uses concept of five state as important during execution of the process 

1) Ready queue
2) running 
3) Waiting queue
4) start state
5) exit state


there are five important events;

1) start to Ready 
2) Ready to running
3) running to waiting
4) running to exit
5) waiting to Ready 


function named ruunning takes care of event 3 and 4 , while function named fillreadyqueue takes care of event 1,2 and 5

 Ready queue is implemented by a priority queue
 the code runs on timestamp basis, so every event is checked at each time frame.

 Output shows the value of timestamp where any of five events has occured. It also shows the Waiting time of each process as well their turnaround time. It end with command "all process over".



Case 1: 

Input

0 100 2 90 2 80 3 70 2 60 2 10 -1
2 80 2 80 2 50 3 70 2 40 2 10 -1
3 70 2 70 2 40 3 70 2 20 2 10 -1
4 10 2 60 2 30 3 70 2 10 2 10 -1
5 3 2 3 2 3 -1
6 5 -1
10 200 2 3 -1

Output

no of processes 7

0::process-> 0 inserted 
0::process-> 0 run_2_exit 
0::process-> 0 ready_2_run 
2::process-> 1 inserted 
3::process-> 2 inserted 
4::process-> 3 inserted 
5::process-> 4 inserted 
6::process-> 5 inserted 
10::process-> 6 inserted 
100::process-> 0 run_2_wait 
100::process-> 4 ready_2_run 
102::process-> 0 wait_2_ready 
103::process-> 4 run_2_wait 
103::process-> 5 ready_2_run 
105::process-> 4 wait_2_ready 
108::process-> 5 run_2_exit 
108::process-> 4 ready_2_run 
111::process-> 4 run_2_wait 
111::process-> 3 ready_2_run 
113::process-> 4 wait_2_ready 
121::process-> 3 run_2_wait 
121::process-> 4 ready_2_run 
123::process-> 3 wait_2_ready 
124::process-> 4 run_2_exit 
124::process-> 3 ready_2_run 
184::process-> 3 run_2_wait 
184::process-> 2 ready_2_run 
186::process-> 3 wait_2_ready 
254::process-> 2 run_2_wait 
254::process-> 3 ready_2_run 
256::process-> 2 wait_2_ready 
284::process-> 3 run_2_wait 
284::process-> 2 ready_2_run 
287::process-> 3 wait_2_ready 
354::process-> 2 run_2_wait 
354::process-> 3 ready_2_run 
356::process-> 2 wait_2_ready 
424::process-> 3 run_2_wait 
424::process-> 2 ready_2_run 
426::process-> 3 wait_2_ready 
464::process-> 2 run_2_wait 
464::process-> 3 ready_2_run 
467::process-> 2 wait_2_ready 
474::process-> 3 run_2_wait 
474::process-> 2 ready_2_run 
476::process-> 3 wait_2_ready 
544::process-> 2 run_2_wait 
544::process-> 3 ready_2_run 
546::process-> 2 wait_2_ready 
554::process-> 3 run_2_exit 
554::process-> 2 ready_2_run 
574::process-> 2 run_2_wait 
574::process-> 1 ready_2_run 
576::process-> 2 wait_2_ready 
654::process-> 1 run_2_wait 
654::process-> 2 ready_2_run 
656::process-> 1 wait_2_ready 
664::process-> 2 run_2_exit 
664::process-> 1 ready_2_run 
744::process-> 1 run_2_wait 
744::process-> 0 ready_2_run 
746::process-> 1 wait_2_ready 
834::process-> 0 run_2_wait 
834::process-> 1 ready_2_run 
836::process-> 0 wait_2_ready 
884::process-> 1 run_2_wait 
884::process-> 0 ready_2_run 
887::process-> 1 wait_2_ready 
964::process-> 0 run_2_wait 
964::process-> 1 ready_2_run 
967::process-> 0 wait_2_ready 
1034::process-> 1 run_2_wait 
1034::process-> 0 ready_2_run 
1036::process-> 1 wait_2_ready 
1104::process-> 0 run_2_wait 
1104::process-> 1 ready_2_run 
1106::process-> 0 wait_2_ready 
1144::process-> 1 run_2_wait 
1144::process-> 0 ready_2_run 
1146::process-> 1 wait_2_ready 
1204::process-> 0 run_2_wait 
1204::process-> 1 ready_2_run 
1206::process-> 0 wait_2_ready 
1214::process-> 1 run_2_exit 
1214::process-> 0 ready_2_run 
1224::process-> 0 run_2_exit 
1224::process-> 6 ready_2_run 
1424::process-> 6 run_2_exit 
1424:: running over 

 waiting time 
 process -> 0 803
 process -> 1 871
 process -> 2 370
 process -> 3 349
 process -> 4 106
 process -> 5 97
 process -> 6 1214

 turnaround time 
 process -> 0 1224
 process -> 1 1212
 process -> 2 661
 process -> 3 550
 process -> 4 119
 process -> 5 102
 process -> 6 1414
all process over



 Case 2:
 
 Input 

0 5 -1
1 3 2 3 2 3 -1
6 10 2 60 2 30 3 70 2 10 2 10 -1
23 3 2 3 2 3 -1
24 70 2 70 2 40 3 70 2 20 2 10 -1
25 3 2 3 2 3 -1
26 80 2 80 2 50 3 70 2 40 2 10 -1
27 3 2 3 2 3 -1
28 25 2 10 -1
29 3 2 3 2 3 -1
31 3 2 3 2 3 -1
33 3 2 3 2 3 -1
35 3 2 3 2 3 -1
40 3 2 3 2 3 -1
40 3 2 3 2 3 -1
42 3 2 3 2 3 -1
43 3 2 3 2 3 -1
45 3 2 3 2 3 -1



Output 


no of processes 18

0::process-> 0 inserted 
0::process-> 0 run_2_exit 
0::process-> 0 ready_2_run 
1::process-> 1 inserted 
5::process-> 0 run_2_exit 
5::process-> 1 ready_2_run 
6::process-> 2 inserted 
8::process-> 1 run_2_wait 
8::process-> 2 ready_2_run 
10::process-> 1 wait_2_ready 
18::process-> 2 run_2_wait 
18::process-> 1 ready_2_run 
20::process-> 2 wait_2_ready 
21::process-> 1 run_2_wait 
21::process-> 2 ready_2_run 
23::process-> 3 inserted 
23::process-> 1 wait_2_ready 
24::process-> 4 inserted 
25::process-> 5 inserted 
26::process-> 6 inserted 
27::process-> 7 inserted 
28::process-> 8 inserted 
29::process-> 9 inserted 
31::process-> 10 inserted 
33::process-> 11 inserted 
35::process-> 12 inserted 
40::process-> 13 inserted 
40::process-> 14 inserted 
42::process-> 15 inserted 
43::process-> 16 inserted 
45::process-> 17 inserted 
81::process-> 2 run_2_wait 
81::process-> 3 ready_2_run 
83::process-> 2 wait_2_ready 
84::process-> 3 run_2_wait 
84::process-> 7 ready_2_run 
86::process-> 3 wait_2_ready 
87::process-> 7 run_2_wait 
87::process-> 15 ready_2_run 
89::process-> 7 wait_2_ready 
90::process-> 15 run_2_wait 
90::process-> 16 ready_2_run 
92::process-> 15 wait_2_ready 
93::process-> 16 run_2_wait 
93::process-> 17 ready_2_run 
95::process-> 16 wait_2_ready 
96::process-> 17 run_2_wait 
96::process-> 3 ready_2_run 
98::process-> 17 wait_2_ready 
99::process-> 3 run_2_wait 
99::process-> 7 ready_2_run 
101::process-> 3 wait_2_ready 
102::process-> 7 run_2_wait 
102::process-> 15 ready_2_run 
104::process-> 7 wait_2_ready 
105::process-> 15 run_2_wait 
105::process-> 16 ready_2_run 
107::process-> 15 wait_2_ready 
108::process-> 16 run_2_wait 
108::process-> 17 ready_2_run 
110::process-> 16 wait_2_ready 
111::process-> 17 run_2_wait 
111::process-> 3 ready_2_run 
113::process-> 17 wait_2_ready 
114::process-> 3 run_2_exit 
114::process-> 7 ready_2_run 
117::process-> 7 run_2_exit 
117::process-> 15 ready_2_run 
120::process-> 15 run_2_exit 
120::process-> 16 ready_2_run 
123::process-> 16 run_2_exit 
123::process-> 17 ready_2_run 
126::process-> 17 run_2_exit 
126::process-> 13 ready_2_run 
129::process-> 13 run_2_wait 
129::process-> 14 ready_2_run 
131::process-> 13 wait_2_ready 
132::process-> 14 run_2_wait 
132::process-> 1 ready_2_run 
134::process-> 14 wait_2_ready 
135::process-> 1 run_2_exit 
135::process-> 11 ready_2_run 
138::process-> 11 run_2_wait 
138::process-> 12 ready_2_run 
140::process-> 11 wait_2_ready 
141::process-> 12 run_2_wait 
141::process-> 13 ready_2_run 
143::process-> 12 wait_2_ready 
144::process-> 13 run_2_wait 
144::process-> 14 ready_2_run 
146::process-> 13 wait_2_ready 
147::process-> 14 run_2_wait 
147::process-> 11 ready_2_run 
149::process-> 14 wait_2_ready 
150::process-> 11 run_2_wait 
150::process-> 12 ready_2_run 
152::process-> 11 wait_2_ready 
153::process-> 12 run_2_wait 
153::process-> 13 ready_2_run 
155::process-> 12 wait_2_ready 
156::process-> 13 run_2_exit 
156::process-> 14 ready_2_run 
159::process-> 14 run_2_exit 
159::process-> 11 ready_2_run 
162::process-> 11 run_2_exit 
162::process-> 12 ready_2_run 
165::process-> 12 run_2_exit 
165::process-> 5 ready_2_run 
168::process-> 5 run_2_wait 
168::process-> 9 ready_2_run 
170::process-> 5 wait_2_ready 
171::process-> 9 run_2_wait 
171::process-> 10 ready_2_run 
173::process-> 9 wait_2_ready 
174::process-> 10 run_2_wait 
174::process-> 5 ready_2_run 
176::process-> 10 wait_2_ready 
177::process-> 5 run_2_wait 
177::process-> 9 ready_2_run 
179::process-> 5 wait_2_ready 
180::process-> 9 run_2_wait 
180::process-> 10 ready_2_run 
182::process-> 9 wait_2_ready 
183::process-> 10 run_2_wait 
183::process-> 5 ready_2_run 
185::process-> 10 wait_2_ready 
186::process-> 5 run_2_exit 
186::process-> 9 ready_2_run 
189::process-> 9 run_2_exit 
189::process-> 10 ready_2_run 
192::process-> 10 run_2_exit 
192::process-> 8 ready_2_run 
217::process-> 8 run_2_wait 
217::process-> 2 ready_2_run 
219::process-> 8 wait_2_ready 
247::process-> 2 run_2_wait 
247::process-> 8 ready_2_run 
250::process-> 2 wait_2_ready 
257::process-> 8 run_2_exit 
257::process-> 4 ready_2_run 
327::process-> 4 run_2_wait 
327::process-> 2 ready_2_run 
329::process-> 4 wait_2_ready 
397::process-> 2 run_2_wait 
397::process-> 4 ready_2_run 
399::process-> 2 wait_2_ready 
467::process-> 4 run_2_wait 
467::process-> 2 ready_2_run 
469::process-> 4 wait_2_ready 
477::process-> 2 run_2_wait 
477::process-> 4 ready_2_run 
479::process-> 2 wait_2_ready 
517::process-> 4 run_2_wait 
517::process-> 2 ready_2_run 
520::process-> 4 wait_2_ready 
527::process-> 2 run_2_exit 
527::process-> 4 ready_2_run 
597::process-> 4 run_2_wait 
597::process-> 6 ready_2_run 
599::process-> 4 wait_2_ready 
677::process-> 6 run_2_wait 
677::process-> 4 ready_2_run 
679::process-> 6 wait_2_ready 
697::process-> 4 run_2_wait 
697::process-> 6 ready_2_run 
699::process-> 4 wait_2_ready 
777::process-> 6 run_2_wait 
777::process-> 4 ready_2_run 
779::process-> 6 wait_2_ready 
787::process-> 4 run_2_exit 
787::process-> 6 ready_2_run 
837::process-> 6 run_2_exit 
837:: running over 

 waiting time 
 process -> 0 0
 process -> 1 121
 process -> 2 320
 process -> 3 78
 process -> 4 472
 process -> 5 148
 process -> 6 597
 process -> 7 77
 process -> 8 192
 process -> 9 147
 process -> 10 148
 process -> 11 116
 process -> 12 117
 process -> 13 103
 process -> 14 106
 process -> 15 65
 process -> 16 67
 process -> 17 68

 turnaround time 
 process -> 0 5
 process -> 1 134
 process -> 2 521
 process -> 3 91
 process -> 4 763
 process -> 5 161
 process -> 6 811
 process -> 7 90
 process -> 8 229
 process -> 9 160
 process -> 10 161
 process -> 11 129
 process -> 12 130
 process -> 13 116
 process -> 14 119
 process -> 15 78
 process -> 16 80
 process -> 17 81

all process over 




 
