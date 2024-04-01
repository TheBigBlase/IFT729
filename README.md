# IFT729
Student project for IFT729 (aka real time systems)

# front end
front end is in `src/front-end`. Run `npm install socket.io express` to install
libs.
run with `node ./server.js` in `src/front-end` to run front end.
Check `localhost:3000/drawer` or `localhost:3000/guesser` to load relevent
pages.

# backend
since for now front end will rely on websocket, ZMQ seems reasonable to use. 
It would be easy to understand and prototype. 
On the otherside, boost::asio would be very powerful.

Its buildable w/ cmake, go where you wanna build (eg, `src/backend/build`) and 
run `cmake <../> -DCMAKE_BUILD_TYPE={Debug,Release}` where `../` points to the
dir where `CMakeLists.txt` is.

After that, we might try to implement faster protocol, (we _have_ to do
real time after all)

choices we have (for frontend):
+ webrtc (real time coms) -> some protocols are build on top of udp
    + fast enough
    + flexible enough
+ webassemlby
    + will be slower, harder to learn
    + wayyyy more flexibility + powerful
