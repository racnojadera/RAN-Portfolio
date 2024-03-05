var timerTime = 0; //https://stackoverflow.com/questions/8578006/current-time-in-setinterval
var timerRunning = false;
function showPomodoroScreen() {
     let pomoWindow = document.querySelector(".pomo_window");
    //https://www.w3schools.com/js/js_htmldom_css.asp
    pomoWindow.style.display = "flex";

    let mainWindow = document.querySelector(".main_div");
    mainWindow.style.display = "none";

}

function loadTime(event) {
    let source = event.target;
    if (source.value.length == 4) { // https://stackoverflow.com/questions/4313841/insert-a-string-at-a-specific-index https://www.w3schools.com/jsref/jsref_slice_string.asp
        console.log("time loaded")
        source.value = source.value.slice(0, 2).concat(':').concat(source.value.slice(2, source.value.length));
    }
}


function startTimer() {
    if (timerRunning) {
        alert("Launching")
        return;
    }
    timerRunning = true;
    document.querySelector("#start_timer_btn").disabled = true;
    let timerInput = document.querySelector(".time_input");
    time = timerInput.value;
    minutes = Number(time.slice(0,2))
    seconds = Number(time.slice(3, 5))
    seconds += (minutes*60)
    timerTime = seconds;
    if (timerTime <= 0 || Number.isNaN(timerTime) || timerTime > 60*60 || time.includes('-')) { //https://www.w3schools.com/jsref/jsref_isnan_number.asp
        timerTime = 0;
        alert("Invalid time amount has been input");
        timerInput.value = '';
        timerRunning = false;
        return;
    }
    timerTime -= 1;
    timerInput.value = String(Math.floor(timerTime/60)).padStart(2, '0').concat(":").concat(String(timerTime%60).padStart(2, '0'));



    var countdown = setInterval(function() {
        let timerInput = document.querySelector(".time_input");
        timerTime = timerTime - 1;
        console.log(timerTime);
        minutes = Math.floor(timerTime/60);
        seconds = timerTime%60;
        timerInput.value = String(minutes).concat(":").concat(String(seconds).padStart(2, '0'));
        if (timerTime <= 0) {
            clearInterval(countdown)
            document.querySelector(".pomo_start_button").disabled = false;
            timerTime = 0;
            timerRunning = false;
        }
    }, 1000) //https://developer.mozilla.org/en-US/docs/Web/API/WindowOrWorkerGlobalScope/setInterval
}

document.querySelector(".pomo_timer").addEventListener("click", (event) => showPomodoroScreen());
document.querySelector(".time_input").addEventListener("input", (event) => loadTime(event))
document.querySelector("#end_timer_btn").addEventListener("click", function() {
    if (!timerRunning) {
        return;
    }
    timerTime = 1;
    let timerInput = document.querySelector(".time_input");
    timerInput.value = "00:00";
    timerRunning = false;
});
document.querySelector("#start_timer_btn").addEventListener("click", (event) => startTimer());
document.querySelector("#close_pomo_btn").addEventListener("click", function () {
    if (timerRunning) {
        return;
    }
    document.querySelector(".pomo_window").style.display = "none";
    document.querySelector(".main_div").style.display = "flex";
})