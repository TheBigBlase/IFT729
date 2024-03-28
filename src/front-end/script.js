document.addEventListener("DOMContentLoaded", function() {
    const canvas = document.getElementById('canvas');
    const ctx = canvas.getContext('2d');
    let isDrawing = false; // Variable pour suivre si le bouton de la souris est enfoncé

    canvas.addEventListener('mousedown', function(event) {
        isDrawing = true; // Le bouton de la souris est enfoncé, commencez à dessiner
        draw(event); // Commencez à dessiner à la position initiale
    });

    canvas.addEventListener('mousemove', function(event) {
        if (isDrawing) {
            draw(event); // Si le bouton de la souris est enfoncé, continuez à dessiner
        }
    });

    canvas.addEventListener('mouseup', function() {
        isDrawing = false; // Le bouton de la souris est relâché, arrêtez de dessiner
    });


    function draw(event) {
        const rect = canvas.getBoundingClientRect();
        const x = event.clientX - rect.left;
        const y = event.clientY - rect.top;

        let pixelData;
        // const pixelData = ctx.getImageData(x, y, 1, 1);
        const newColor = [255, 0, 0, 255]; // Exemple : rouge opaque

        // Mettre à jour la couleur du pixel
        const padding = 3;
        for (let abs = x-padding; abs < x+padding; abs++) {
            for (let ord = y-padding; ord < y+padding; ord++) {
                let pixelData = ctx.getImageData(abs, ord, 1, 1);
                for (let i = 0; i < 4; i++) {
                    pixelData.data[i] = newColor[i];
                }
                ctx.putImageData(pixelData, abs, ord);
            }
        }

        // Mettre à jour les données du pixel sur le canvas
        // ctx.putImageData(pixelData, x, y);

        console.log(`Coordonnées du pixel cliqué : (${x}, ${y})`);
        // console.log(`Couleur du pixel cliqué : rgba(${pixelData.data[0]}, ${pixelData.data[1]}, ${pixelData.data[2]}, ${pixelData.data[3] / 255})`);
    }
});