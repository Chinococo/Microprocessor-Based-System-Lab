const express = require("express");
const path = require("path");
const child_process = require("child_process");
const app = express();

app.use(express.static(__dirname))

app.get("/", (req, res) => {
    res.sendFile(path.join(__dirname, "index.html"))
})
app.get("/auto_detect",(req,res)=>{
	const process = child_process.spawn('python',['Lab5.py']);
	process.stdout.on('data',(data)=>{
		console.log(`Child process output${data}`);
		res.send(data);
	})
})

app.get("/gpio", (req, res) => {
    console.log(req.query.LED1);
    console.log(req.query.LED2);
    console.log(req.query.ON);
    console.log(req.query.OFF);
    excute(1, req.query.ON);
    excute(2, req.query.ON);
    excute(3, req.query.ON);
    excute(4, req.query.ON);
})

app.get("/gpio_shine", (req, res) => {
    exec(`./Mode_Shine ${req.query.ShineTimes}`, (error, stdout, stderr) => {
        if (error) {
            console.error(`exec error: ${error}`)
        }
        //res.send(`${stdout}`)
    })
    console.log(`./Mode_Shine ${req.query.ShineTimes}`)
})

function excute(NUMBER, STATE) {
    console.log(NUMBER,STATE);	
    if (STATE == "true") {
	process = child_process.spawn('./index', [`LED${NUMBER}`, 'on']);
	process.stdout.on('data',(data)=>{
		console.log(`Child process output${data}`);
		res.send(data);
	})
        console.log(`./index LED${NUMBER} on`)
    } else {
        process = child_process.spawn(`./index LED${NUMBER} off`);
	process.stdout.on('data',(data)=>{
		console.log(`Child process output${data}`);
		res.send(data);
	})
        console.log(`./index LED${NUMBER} off`)
    }
}

const PORT = process.env.PORT || 8080
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}.`)
})

