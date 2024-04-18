document.addEventListener("DOMContentLoaded", function () {
	let submitButton = document.getElementById('requestGameList');
	submitButton.addEventListener('click', function () {
		console.log("asked for a new room");
		socket.send("ROOMLIST:")
	});
});
