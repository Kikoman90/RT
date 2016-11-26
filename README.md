# RT

RT is a 42 project developped by <a href="https://github.com/sganon">sganon</a>, <a href="https://github.com/joboyer">joboyer</a>, <a href="https://github.com/Kikoman90">fsidler</a> and me, which is designed to further students' understanding of the concepts behind raytracing.
<img align="center" src="http://image.noelshack.com/fichiers/2016/46/1479406467-rt-limited.png" width="100%" />
<img align="center" src="http://image.noelshack.com/fichiers/2016/46/1479406593-rt-texture.png" width="100%" />
<img align="center" src="http://image.noelshack.com/fichiers/2016/46/1479406725-rt-sphere.png" width="100%" />
<div align=center><img align="center" src="http://image.noelshack.com/fichiers/2016/46/1479406817-rt-hud.png" width="50%" /></div>

The scene's and objects' parameters can be modified in real-time. This software also uses multithreading to speed up calculations.<br />
The program supports multiple lights and objects in a scene.<br />
Any object can have a coefficent of refraction (except for the plane), transparency (except for the plane) and reflection.<br />
Any object can be cut (example: make a hemisphere from a sphere).<br />
Any object can have a texture (bmp format, perlin sound or checkerboard).<br />
The program supports sepia, and black and white filters.<br />
The proram can take a screenshot of a scene.<br />


Several options are available (see [Shortcuts](https://github.com/jfortin42/RT#shortcuts) section for more info)
* Select objects within the scene
* Translate and rotate the camera
* Translate and rotate the selected object
* Change the radius/angle of the selected object
* Change the maximum number of reflections
* Rotate textures
* Increase/decrease anti-aliasing
* Increase processing speed (may reduce quality)


## Install & launch
```bash
git clone https://github.com/jfortin42/RT ~/RT
cd ~/RT && make && ./RT scene/scene1.rt
```
Launch the program with one parameter: the name of the scene you would like to open.
The input file has to follow a predefined layout. A parser implemented in the program will check for layout errors.<br />

Example : ⇣
```bash
./RT scenes/scene1.rt
```
## Shortcuts

Once the scene is rendered, you can select/unselect objects by using the <kbd>&nbsp;left mouse button&nbsp;</kbd>.

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
<td valign="top" height="30px">Exit the program</td>
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
<td valign="top" height="30px">Increase/decrease processing speed</td>
<td valign="top" align="center"><kbd>&nbsp;left shift&nbsp;</kbd></td>
</tr>
</tbody>
</table>
## Contact & contribute
To contact me or to improve RT, feel free to send me an email at **jfortin@student.42.fr**
