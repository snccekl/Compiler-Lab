FUNCTION max : 
PARAM a
PARAM b
IF a >= b GOTO label1
GOTO label2
LABEL label1 : 
RETURN a
GOTO label3
LABEL label2 : 
RETURN b
LABEL label3 : 
FUNCTION knapsack : 
PARAM n
PARAM w
PARAM v
PARAM x
PARAM C
DEC V 160000 
temp6 := #0
i := temp6
LABEL label4 : 
IF i <= n GOTO label5
GOTO label6
LABEL label5 : 
temp13 := i * #800
temp10 := &V + temp13
temp15 := #0
temp16 := temp15 * #4
temp17 := temp10 + temp16
temp19 := #0
*temp17 := temp19
temp23 := #1
temp20 := i + temp23
i := temp20
GOTO label4
LABEL label6 : 
temp25 := #0
j := temp25
LABEL label7 : 
IF j <= C GOTO label8
GOTO label9
LABEL label8 : 
temp32 := #0
temp33 := temp32 * #800
temp29 := &V + temp33
temp35 := j * #4
temp36 := temp29 + temp35
temp38 := #0
*temp36 := temp38
temp42 := #1
temp39 := j + temp42
j := temp39
GOTO label7
LABEL label9 : 
temp44 := #1
i := temp44
LABEL label10 : 
IF i <= n GOTO label11
GOTO label12
LABEL label11 : 
temp48 := #1
j := temp48
LABEL label13 : 
IF j <= C GOTO label14
GOTO label15
LABEL label14 : 
temp57 := #1
temp54 := i - temp57
temp58 := temp54 * #4
temp59 := w + temp58
IF j < *temp59 GOTO label16
GOTO label17
LABEL label16 : 
temp64 := i * #800
temp61 := &V + temp64
temp66 := j * #4
temp67 := temp61 + temp66
temp74 := #1
temp71 := i - temp74
temp75 := temp71 * #800
temp69 := &V + temp75
temp77 := j * #4
temp78 := temp69 + temp77
*temp67 := *temp78
GOTO label18
LABEL label17 : 
temp83 := i * #800
temp80 := &V + temp83
temp85 := j * #4
temp86 := temp80 + temp85
temp94 := #1
temp91 := i - temp94
temp95 := temp91 * #800
temp89 := &V + temp95
temp97 := j * #4
temp98 := temp89 + temp97
temp107 := #1
temp104 := i - temp107
temp108 := temp104 * #800
temp102 := &V + temp108
temp116 := #1
temp113 := i - temp116
temp117 := temp113 * #4
temp118 := w + temp117
temp109 := j - *temp118
temp119 := temp109 * #4
temp120 := temp102 + temp119
temp125 := #1
temp122 := i - temp125
temp126 := temp122 * #4
temp127 := v + temp126
temp99 := *temp120 + *temp127
ARG temp99
ARG *temp98
temp128 := CALL max
*temp86 := temp128
LABEL label18 : 
temp132 := #1
temp129 := j + temp132
j := temp129
GOTO label13
LABEL label15 : 
temp136 := #1
temp133 := i + temp136
i := temp133
GOTO label10
LABEL label12 : 
j := C
i := n
LABEL label19 : 
temp141 := #1
IF i >= temp141 GOTO label20
GOTO label21
LABEL label20 : 
temp147 := i * #800
temp144 := &V + temp147
temp149 := j * #4
temp150 := temp144 + temp149
temp156 := #1
temp153 := i - temp156
temp157 := temp153 * #800
temp151 := &V + temp157
temp159 := j * #4
temp160 := temp151 + temp159
IF *temp150 > *temp160 GOTO label22
GOTO label23
LABEL label22 : 
temp164 := i * #4
temp165 := x + temp164
temp167 := #1
*temp165 := temp167
temp175 := #1
temp172 := i - temp175
temp176 := temp172 * #4
temp177 := w + temp176
temp168 := j - *temp177
j := temp168
GOTO label24
LABEL label23 : 
temp181 := i * #4
temp182 := x + temp181
temp184 := #0
*temp182 := temp184
LABEL label24 : 
temp188 := #1
temp185 := i - temp188
i := temp185
GOTO label19
LABEL label21 : 
temp193 := n * #800
temp190 := &V + temp193
temp195 := C * #4
temp196 := temp190 + temp195
RETURN *temp196
FUNCTION main : 
DEC mw 60 
DEC mv 60 
DEC mx 60 
temp198 := #10
mC := temp198
temp200 := #5
mn := temp200
temp204 := #0
temp205 := temp204 * #4
temp206 := &mw + temp205
temp208 := #2
*temp206 := temp208
temp212 := #1
temp213 := temp212 * #4
temp214 := &mw + temp213
temp216 := #2
*temp214 := temp216
temp220 := #2
temp221 := temp220 * #4
temp222 := &mw + temp221
temp224 := #6
*temp222 := temp224
temp228 := #3
temp229 := temp228 * #4
temp230 := &mw + temp229
temp232 := #5
*temp230 := temp232
temp236 := #4
temp237 := temp236 * #4
temp238 := &mw + temp237
temp240 := #4
*temp238 := temp240
temp244 := #0
temp245 := temp244 * #4
temp246 := &mv + temp245
temp248 := #6
*temp246 := temp248
temp252 := #1
temp253 := temp252 * #4
temp254 := &mv + temp253
temp256 := #3
*temp254 := temp256
temp260 := #2
temp261 := temp260 * #4
temp262 := &mv + temp261
temp264 := #5
*temp262 := temp264
temp268 := #3
temp269 := temp268 * #4
temp270 := &mv + temp269
temp272 := #4
*temp270 := temp272
temp276 := #4
temp277 := temp276 * #4
temp278 := &mv + temp277
temp280 := #6
*temp278 := temp280
ARG mC
ARG &mx
ARG &mv
ARG &mw
ARG mn
temp287 := CALL knapsack
ms := temp287
WRITE ms
temp289 := #0
RETURN temp289
