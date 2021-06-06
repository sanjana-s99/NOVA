var temparr = [30.10,30.90,30.11,];
var humiarr = [75,74,76];
var soilmarr = [25.81,25.23,25.94];
var h2oarr = [50,50,50];
var index = 0;
setInterval(function(){
    document.getElementById('temp').innerHTML = temparr[index++ % temparr.length] + '°C';
    document.getElementById('humi').innerHTML = humiarr[index++ % humiarr.length] + '%';
    document.getElementById('soilm').innerHTML = soilmarr[index++ % soilmarr.length] + '%';
    document.getElementById('h2o').innerHTML = h2oarr[index++ % h2oarr.length] + '%';
}, 5000)