const DashButton=require("dash-button");
const PHY_ADDR="xx:xx:xx:xx:xx:xx";
let button=new DashButton(PHY_ADDR);

const exec=require('child_process').exec;
const exec_1=require('child_process').exec;
const exec_2=require('child_process').exec;

console.log("Ready...");
let i=0;

button.addListener(()=>{
	console.log("Receptioning");
	exec('ps -ef | grep motion | grep -v grep | wc -l',function(err,stdout,stderr){
		if(err){
			console.log(err);
		}else{
			if(stdout==1){
				console.log('-- construct --------------------------------------');
				
				exec_1('../cpp/load_configure | espeak -a 25',(err_m,stdout_m,stderr_m)=>{
					if(err_m){console.log(err_m);}
					console.log(stdout_m);
				});
				exec_2('sudo motion && date',(err_m,stdout_m,stderr_m)=>{
					if(err_m){console.log(err_m);}
					console.log(stdout_m);
					console.log("camera on");
				});
			}else if(stdout==2){
				console.log('-- destroy ----------------------------------------');
				
				exec_1('sudo killall motion && date',(err_m,stdout_m,stderr_m)=>{
					if(err_m){console.log(err_m);}
					console.log(stdout_m);
					console.log("camera off");
				});
				exec_2('espeak -a 25 "The motion process was  destroyed"',(err_m,stdout_m,stferr_m)=>{
					if(err_m){console.log(err_m);}
					console.log(stdout_m);
				});
			}
		}
	});
});
