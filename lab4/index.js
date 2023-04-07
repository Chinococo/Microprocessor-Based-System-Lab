const express = require("express")
const path = require("path")
const app = express()
const {exec} = require("child_process")

app.use(express.static(__dirname))

app.get("/", (req, res) => {
	res.sendFile(path.join(__dirname, "index.html"))
})

app.get("/gpio", (req, res) => {
	res.send(console.log(req.query.option1));
	res.send(console.log(req.query.option2));
	res.send(console.log(req.query.option3));
	res.send(console.log(req.query.option4));
	exec("dir", (error, stdout, stderr) => {
		if (error) {
			console.error(`exec error: ${error}`)
		}
		res.send(`${stdout}`)
	})
})




const PORT = process.env.PORT || 8080
app.listen(PORT, () => {
	console.log(`Server is running on port ${PORT}.`)
})

