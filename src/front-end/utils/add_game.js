document.addEventListener("DOMContentLoaded", function() {
    var submitButton = document.getElementById('requestNewGame');
    submitButton.addEventListener('click', function() {
        console.log("asked for a new room");
		socket.send("NEWROOM:")
    });
});
