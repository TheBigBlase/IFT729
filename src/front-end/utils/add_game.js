document.addEventListener("DOMContentLoaded", function() {
    var submitButton = document.getElementById('requestNewGame');
    submitButton.addEventListener('click', function() {
		socket.send("NEWROOM")
        console.log("asked for a new room");
    });
});
