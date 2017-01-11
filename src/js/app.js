const DashButton=require("dash-button");
const PHY_ADDR="34:d2:70:1a:8d:9b";
let button=new DashButton(PHY_ADDR);

const exec=require('child_process').exec;
const exec_1=require('child_process').exec;

console.log("Ready...");
let i=0;

button.addListener(()=>{
	exec('ps -ef | grep motion | grep -v grep | wc -l',function(err,stdout,stderr){
		if(err){
			console.log(err);
		}else{
			if(stdout==0){
				console.log('------------------------------------------');
				exec_1('sudo motion && date',(err_m,stdout_m,stderr_m)=>{
					if(err_m){console.log(err_m);}
					console.log(stdout_m);
					console.log("camera on");
				});
			}else if(stdout==1){
				console.log('------------------------------------------');
				exec_1('sudo killall motion && date',(err_m,stdout_m,stderr_m)=>{
					if(err_m){console.log(err_m);}
					console.log(stdout_m);
					console.log("camera off");
				});
			
			}
		}
	});
});
