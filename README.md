<img src="img/logo-lg.png" title="jrelo">

<h1><a target="_blank" href="https://jrelo.com">Jrelo</a> - control and monitoring of remote devices.</h1>
<h2> Manage Arduino over the Internet.</h2>
<br>
<h2>
    Implementations of units for the Arduino MEGA 2560.
</h2>

<img src="img/img1.jpg" title="Arduino and SIM900">

<ui>
    <li><b>EthernetPUnit</b> - unit uses EthernetShield W5100. Data transmission via HTTP Polling.</li>
    <li><b>EthernetPXUnit</b> - unit uses EthernetShield W5100. Data transmission via HTTP Polling (with StringBox).
    </li>
    <li><b>EthernetWUnit</b> - unit uses EthernetShield W5100. Data transmission via WebSocket.</li>
    <li><b>EthernetWXUnit</b> - unit uses EthernetShield W5100. Data transmission via WebSocket (with StringBox).
    </li>
    <li><b>GSMPXUnit</b> - unit uses SIM board. Data transmission via HTTP(S) Polling (with StringBox).</li>
</ui>
<p><i>See examples <a target="_blank" href="https://jrelo.com/archives/category/examples-ru/arduino">here</a>.</i></p>
<br>
<h2>
    Modules (compatible with all unit implementations)
</h2>

<ui>
    <li><b>BMP180PressureModule</b> - BMP180 sensor for measuring pressure (wrapper).</li>
    <li><b>BMP180TemperatureModule</b> - BMP180 sensor for temperature measurement (wrapper).</li>
    <li><b>DallasTemperatureModule</b> - Dallas 18B20 sensor for temperature measurement (wrapper).</li>
    <li><b>DHTHumidityModule</b> - DHT sensor for measuring humidity (wrapper).</li>
    <li><b>DHTTemperatureModule</b> - DHT sensor for temperature measurement (wrapper).</li>
    <li><b>GPSModule</b> - GPS module NEO-6M (wrapper).</li>
    <li><b>EventSchedulerModule</b>, <b>WorkSchedulerModule</b> - event schedule.</li>
    <li><b>LifetimeModule</b> - lifetime.</li>
    <li><b>MultiRelayModule</b> - relay set.</li>
    <li><b>MultiRelaySSModule</b> - relay set (state saving).</li>
    <li><b>RelayModule</b> - relay.</li>
    <li><b>RelaySSModule</b> - relay (state saving).</li>
    <li><b>TimeModule</b> - real time in unit.</li>
</ui>


<p><i>Wrapper - adapter class using the functionality of a third-party library</i></p>
<br>
<h2>
    Utilities for working with strings
</h2>
<div>
    <h3>StringBox</h3> Storage for string variables allowing dynamic work with arrays characters. Uses its own allocated
    memory to store strings.
    <div>Advantage :</div>
    <ul>
        <li>Does not lead to controller memory fragmentation.</li>
        <li>Automatic defragmentation of own memory.</li>
    </ul>
    <div>Disadvantages :</div>
    <ul>
        <li>Pre-allocation of memory</li>
        <li>Cannot expand memory more than allocated</li>
        <li>128 string limit</li>
    </ul>
</div>
<br>
<div>
    <h3>StringBuffer</h3> Buffer for storing and concatenating strings. StringBuffer with StringBufferUtils may be
    alternatives
    for class String. Uses to work StringBox.
    <div>Advantage :</div>
    <ul>
        <li>Automatically expands memory internal buffer</li>
        <li>Ability to clear unnecessary allocated memory</li>
        <li>Work speed</li>
    </ul>
    <div>Disadvantages :</div>
    <ul>
        <li>StringBox required</li>
    </ul>
</div>
<p><i>See examples <a target="_blank"
                      href="https://github.com/jrelo-com/libraries/blob/master/JreloUtils/examples/StringBox/StringBox.ino">here</a>
    and <a target="_blank"
           href="https://github.com/jrelo-com/libraries/blob/master/JreloUtils/examples/StringBuffer/StringBuffer.ino">here</a>.</i>
</p>

