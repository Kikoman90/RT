# RT

RT is a program developped be me, <a href="https://github.com/sganon">sganon</a> and <a href="https://github.com/joboyer">joboyer</a> for our learning course at 42 school for the exploration of raytracing.
<img align="center" src="http://image.noelshack.com/fichiers/2016/46/1479406467-rt-limited.png" width="100%" />
<img align="center" src="http://image.noelshack.com/fichiers/2016/46/1479406593-rt-texture.png" width="100%" />
<img align="center" src="http://image.noelshack.com/fichiers/2016/46/1479406725-rt-sphere.png" width="100%" />
<div align=center><img align="center" src="http://image.noelshack.com/fichiers/2016/46/1479406817-rt-hud.png" width="50%" /></div>

The scene and objects parameters can be modified in real-time. This software also uses multithreading to fasten up the calculations.<br />
The program support multiple lights and objects in a scene.<br />
Any objects can have a coefficent of refraction (except the plane), transparency (except the plane) and reflection.<br />
Any objects can be cut (example : a sphere become hemisphere).<br />
Any objects can have a texture (bmp format, perlin sound or checkerboard).<br />
The program support the filters black and white and sepia.<br />
The proram can take a screenshot of a scene.<br />


Several options are available (see [Shortcuts](https://github.com/jfortin42/RT#shortcuts) section for more info)
* Select objects within the scene
* Translate and rotate the camera
* Translate and rotate the selected object
* Change the radius/angle of the selected object
* Change the maximum number of reflections
* Rotate textures
* Change the anti-aliasing
* Mode speed


## Install & launch
```bash
git clone https://github.com/jfortin42/RT ~/RT
cd ~/RT && make && ./RT scene/scene1.rt
```
You have to launch the program with a parameter. This is the name of the scene you would like to open at the execution of the program.
The input file has to follow a predefined layout. A parser implemented in the program will check for layout errors.<br />

Example : ⇣
```bash
./RT scenes/scene1.rt
```
## Shortcuts

Once the scene is rendered, you are able to select/unselect objects in the scene by using the <kbd>&nbsp;left mouse button&nbsp;</kbd>.

<table width="100%">
<thead>
<tr>
<td width="40%" height="60px" align="center" cellpadding="0">
<strong>Description</strong>
</td>
<td width="10%" align="center" cellpadding="0">
<span style="width:70px">&nbsp;</span><strong>Key(s)</strong><span style="width:50px">&nbsp;</span>
</td>
</tr>
</thead>
<tbody>
<tr>
<td valign="top" height="30px">Close the program</td>
<td valign="top" align="center"><kbd>&nbsp;esc&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Translate camera/object along local X axis</td>
<td valign="top" align="center"><kbd>&nbsp;A&nbsp;</kbd> <kbd>&nbsp;D&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Translate camera/object along local Y axis</td>
<td valign="top" align="center"><kbd>&nbsp;W&nbsp;</kbd> <kbd>&nbsp;S&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Translate camera/object along local Z axis</td>
<td valign="top" align="center"><kbd>&nbsp;e&nbsp;</kbd> <kbd>&nbsp;q&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Rotate camera/object along local X axis</td>
<td valign="top" align="center"><kbd>&nbsp;◄&nbsp;</kbd> <kbd>&nbsp;►&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Rotate camera/object along local Y axis</td>
<td valign="top" align="center"><kbd>&nbsp;▲&nbsp;</kbd> <kbd>&nbsp;▼&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Increase/decrease the maximum number of reflections</td>
<td valign="top" align="center"><kbd>&nbsp;t&nbsp;</kbd> <kbd>&nbsp;g&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Increase/decrease the radius of object</td>
<td valign="top" align="center"><kbd>&nbsp;.&nbsp;</kbd> <kbd>&nbsp;,&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Enable/disable mode speed</td>
<td valign="top" align="center"><kbd>&nbsp;left shift&nbsp;</kbd></td>
</tr>
</tbody>
</table>
## Contact & contribute
If you want to contact me, or improve RT, just send me a mail at **jfortin@student.42.fr**
