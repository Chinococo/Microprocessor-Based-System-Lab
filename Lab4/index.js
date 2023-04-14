const express = require("express")
const path = require("path")
const { exec } = require("child_process")
const app = express()

app.use(express.static(__dirname))

app.get("/", (req, res) => {
    res.sendFile(path.join(__dirname, "index.html"))
})

app.get("/gpio", (req, res) => {
    res.send(console.log(req.query.option1));
    res.send(console.log(req.query.option2));
    res.send(console.log(req.query.option3));
    res.send(console.log(req.query.option4));
    excute(1, req.query.option1);
    excute(2, req.query.option2);
    excute(3, req.query.option3);
    excute(4, req.query.option4);
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
    if (STATE == "true") {
        exec(`./index LED${NUMBER} on`, (error, stdout, stderr) => {
            if (error) {
                console.error(`exec error: ${error}`)
            }
            //res.send(`${stdout}`)
        })
        console.log(`./index LED${NUMBER} on`)
    } else {
        exec(`./index LED${NUMBER} off`, (error, stdout, stderr) => {
            if (error) {
                console.error(`exec error: ${error}`)
            }
            //res.send(`${stdout}`)
        })
        console.log(`./index LED${NUMBER} off`)
    }
}

const PORT = process.env.PORT || 8080
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}.`)
})

