const address = 'ws://localhost:8888';
let socket = new WebSocket(address);

document.addEventListener("DOMContentLoaded", function () {
	// leaving this as example of how to get response
	// TODO get events
	//     win / lose
	//     new guesses
	//     other's guesses

	let canvas, ctx, canvasData, width, height;

	if (window.location.href.endsWith("guesser")) {
		canvas = document.getElementById('canvas');
		ctx = canvas.getContext('2d');
		width = canvas.getBoundingClientRect().width;
		height = canvas.getBoundingClientRect().height;
		canvasData = ctx.getImageData(0, 0, width, height);
	}

	function store_game_id(id) {
		sessionStorage.setItem("game_id", id);
	}

	function handle_message(msg, id = 0) {
		let res = msg.split(":");
		switch (res[0]) {
			case "PX": {
				// TODO print on guesser side
				let x = res[1], y = res[2];
				// TODO separate files maybe?
                
				if (window.location.href.endsWith("guesser")) {
                    ctx.fillRect(x-3, y-3, 7, 7);
					console.log("PIXEL x: " + x + " y: " + y);
				}
				break;
			}
			case "MSG": {
				ul = document.getElementById("messageList");
				let li = document.createElement("li");
				li.appendChild(document.createTextNode(res[1]));
				ul.appendChild(li);
				break;
			}
			case "WIN":
                window.alert("You found the right word !\n\
                Congrats, you won this one !\n\n\
                New game starting !\n\n");
                window.location.href = "/drawer";
				break;
			case "LOOSE":
                window.alert(res[1]+" found the right word : " + res[2] +"!\n\
                You didn't win this one.\n\n\
                New game starting !\n\n");
				window.location.href = "/guesser"; //temporaire pour quand on va savoir qui est le drawer
                //var canvas = document.getElementById('canvas');
                //var context = canvas.getContext('2d');
                //context.clearRect(0, 0, canvas.width, canvas.height);
			case "ERR":
				break;
			case "ROOM": {
				// TODO do that in batch
				sessionStorage.setItem("id", res[1]);
				res = res.slice(1, undefined);
				let ul = document.getElementById("roomList");
				while (ul.firstChild) {
					ul.removeChild(ul.lastChild);
				}
				for (let elt of res) {
					ul = document.getElementById("roomList");
					let li = document.createElement("li");
					let a = document.createElement("a");
					store_game_id(elt);
					a.setAttribute("href", "guesser");
					a.appendChild(document.createTextNode("Room n°" + elt));
					li.appendChild(a);
					ul.appendChild(li);
				};
				break;
			}
			case "CONN":
				console.log("Connected as player " + res[1]);
				break;
			case "DRAWER": {
				// first is room to go
				let room = res[1];
				let li = document.createElement("li");
				let a = document.createElement("a");
				let ul = document.getElementById("roomList");
				store_game_id(room);
				a.setAttribute("href", "drawer");
				a.appendChild(document.createTextNode("Go to your lobby!"));
				li.appendChild(a);
				ul.appendChild(li);
				break;
			}
			default:
				break;
		}
	}

	socket.onmessage = (msg) => {
		console.log("got msg: " + msg.data);
		handle_message(msg.data);
	}

	socket.onclose = () => {
	}
});
