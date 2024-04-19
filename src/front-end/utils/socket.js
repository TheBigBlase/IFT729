const address = 'ws://localhost:8888';
let socket = new WebSocket(address);

// TODO names
function store_game_id(id) {
	sessionStorage.setItem("game_id", id);
}

function go_to_draw(id, word) {
	sessionStorage.setItem("game_id", id);
	sessionStorage.setItem("word_to_guess", word);
}

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

	function handle_message(msg, id = 0) {
		let res = msg.split(":");
		switch (res[0]) {
			case "PX": {
				// TODO print on guesser side
				let x = res[1], y = res[2];
				// TODO separate files maybe?

				if (window.location.href.endsWith("guesser")) {
					ctx.fillRect(x - 3, y - 3, 7, 7);
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
				window.alert("You found the right word !\n" +
                "Congrats, you won this one !\n\n" + 
                "New game starting !\n\n");
				window.location.href = "drawer";
				break;
			case "LOOSE":
				window.alert("Someone found the right word !\n" + 
                "You didn't win this one.\n\n" + 
                "New game starting !\n\n");
				var canvas = document.getElementById('canvas');
				var context = canvas.getContext('2d');
				context.clearRect(0, 0, canvas.width, canvas.height);
				window.location.href = "guesser";
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
				let word = res[2];
				let ul = document.getElementById("roomList");
				let li = document.createElement("li");
				let a = document.createElement("a");
				a.setAttribute("href", "drawer");
				a.setAttribute("onClick", "go_to_draw(" + room + ", \"" + word + "\")");
				a.appendChild(document.createTextNode("Player " + room + "'s room"));
				li.appendChild(a);
				ul.appendChild(li);

				break;
			};

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
