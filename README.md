# IFT729
Student project for IFT729 (aka real time systems)

# front end
front end is in `src/front-end`. Run `npm install express` to install required modules.
run with `node ./server.js` in `src/front-end` to run front end.
Check `localhost:3000/` to load relevent pages.

# backend
since for now front end will rely on websocket, with a fully async, signle threaded (for now) management.
It uses boost.

We used cmake to build this project. To build it, go where where `CMakeLists.txt` is (ie, `src/backend`)
and run `cmake ./ -Bbuild`.
To run it, go to the build dir and run the executable `guessMyDraw` (if build on release mode).
Then, interact with it through the front end.

After that, we __might__ (update: we dont have time) try to implement faster protocol, (we _have_ to do
real time after all)

choices we have (for frontend):
+ webrtc (real time coms) -> some protocols are build on top of udp
    + fast enough
    + flexible enough
+ webassemlby
    + will be slower, harder to learn
    + wayyyy more flexibility + powerful
