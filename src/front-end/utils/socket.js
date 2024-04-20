const address = 'ws://localhost:8888';
let socket = new WebSocket(address);

function store_game_id(id) {
	sessionStorage.setItem("game_id", id);
}

function store_word(word) {
	sessionStorage.setItem("word_to_guess", word);
}

function showPopup() {
    document.getElementById('popupModal').style.display = 'block';
}

function cancel() {
    window.location.href = "/";
}

document.addEventListener("DOMContentLoaded", function () {

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
				let x = res[1], y = res[2];

				// client side check, but should be useless
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
			case "WIN": {
				window.alert("You found the right word !\n" +
					"Congrats, you won this one !\n\n" + 
					"New game starting !\n\n"
				);
				let word = res[1];
				store_word(word);
				window.location.href = "/drawer"; // we are the next drawer!
				break;
			}
			case "LOOSE":
				if (window.location.href.endsWith("drawer")) {
					window.alert("Someone found your  word : "+ res[2] +" !\n" +
					"New game starting !\n\n"
				);
				}
				else {
					window.alert("Someone found the right word : "+ res[2] +" !\n" + 
					"You didn't win this one.\n\n" + 
					"New game starting !\n\n"
				);
				}
				// we become guesser. If we already were, reset window.
				window.location.href = "/guesser";
				break;
			case "ERR":
				window.alert("ERROR : going to main page");
				window.location.href = "/";
				break;
			case "ROOM": {
				res = res.slice(1, undefined);
				let ul = document.getElementById("roomList");
				while (ul.firstChild) {
					ul.removeChild(ul.lastChild);
				}
				// print all rooms
				for (let elt of res) {
					ul = document.getElementById("roomList");
					let li = document.createElement("li");
					let a = document.createElement("a");
					a.setAttribute("href", "#null");
					a.onclick = function() { 
						console.log(this.getAttribute("valeur")) 
						store_game_id(this.getAttribute("valeur"));
						window.location.href = "/guesser";};
					a.setAttribute("valeur",elt);
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
				showPopup()
				store_game_id(room);
				store_word(word);
				
				break;
			}
			case "START": {
				window.location.href = "/drawer";
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
