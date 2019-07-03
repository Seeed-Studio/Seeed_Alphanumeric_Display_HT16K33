# Grove - alphanumeric Digital Tubes Display

***  

## Introduction of sensor
Grove - alphanumeric Digital Tubes Display,Based on HT16K33,it can display number,and scrolling displaying.


### Notice:
* Support dual(two tubes)&qual(four tubes) alphanumeric Digital Tubes simultaneously. use following API to select   the  type of display.
```
    tube.setTubeType(TYPE_4,I2C_ADDR_AFTER_CHANGE_FOUR);
```
or  

```
    tube.setTubeType(TYPE_2,TYPE_2_DEFAULT_I2C_ADDR);
```
* The example : < combine_two_displays.ino > shows how to combine two displays in one project.



***


This software is written by Jerry Yip for seeed studio and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>


[![Analytics](https://ga-beacon.appspot.com/UA-46589105-3/grove-led-matrix-driver-ht16k33)](https://github.com/igrigorik/ga-beacon)
