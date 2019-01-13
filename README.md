<a target="_blank" href="https://jrelo.com"><img src="img/logo-lg.png" title="jrelo"></a> 
<h1 align="center">Get control of Arduino over the Internet.</h1>
<h2 align="center">For more information, see the <a href="https://github.com/jrelo-com/libraries/wiki">Wiki</a></h2>

<h3>Example of a unit with two modules</h3>

<pre>
#include &lt;EthernetPUnit.h&gt;
#include &lt;LifetimeModule.h&gt;
#include &lt;RelayModule.h&gt;

byte mac[] = { 0xDE, 0xAB, 0xDE, 0xEF, 0xFF, 0xEF };
const char *uuid = "00000000-0000-0000-0000-0000000";
const char *connectionPassword = "00000000000000000000000000000";

EthernetPUnit unit(uuid, connectionPassword, mac);
LifetimeModule ltm(&quot;lt&quot;); // "lt" - module key
RelayModule rm(&quot;rm&quot;, 22); // "rm" - module key, 22 - pin

void setup() {
    Serial.begin(9600);
    unit.putModule(&amp;ltm);
    unit.putModule(&amp;rm);
}

void loop() {
    unit.update();
}
</pre>

<br>
<a href="http://www.youtube.com/watch?feature=player_embedded&v=cMK5AElEt_4
" target="_blank"><img src="https://img.youtube.com/vi/cMK5AElEt_4/0.jpg" 
alt="Arduino. Remote control via the Internet" width="480" height="360" border="10" /></a>
<br>
<img src="img/img0.jpg" title="Arduino and Ethernet"/>
<img src="img/img1.jpg" title="Arduino and SIM900"/>
