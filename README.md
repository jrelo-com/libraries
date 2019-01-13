<a target="_blank" href="https://jrelo.com"><img src="img/logo-lg.png" title="jrelo"></a> 
<h3>Jrelo - Hybrid Message Broker (Hybrid Message Queue)</h3>
<br>
<h1 align="center">Get control of the Arduino over the Internet with Jrelo.</h1>
<h3 align="center">
    Use ready-made implementations of Units and various Modules for the Arduino platform.<br>
    For more information, see the <a href="https://github.com/jrelo-com/libraries/wiki">WIKI</a>.
</h3>

<br>

<h2>Usage</h2>
<p>
    Select the appropriate implementation of the Unit, add ready Modules and unload the sketch - <b>PROFIT !</b> 
</p>
<p>Example of a unit with two modules :</p>


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

<h2>Video</h2>
<a href="http://www.youtube.com/watch?feature=player_embedded&v=cMK5AElEt_4" target="_blank">
    <img src="https://img.youtube.com/vi/cMK5AElEt_4/0.jpg" align="center" alt="Arduino. Remote control via the Internet" width="480" height="360" border="1" />
</a>
