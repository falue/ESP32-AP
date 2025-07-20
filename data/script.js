let ledStatus = false;

function toggleLED(state) {
  fetch(`/led/${state}`)
    .then(response => response.text())
    .then(data => {
      console.log("Response from server: ", data);
      ledStatus = data == "true";
      document.getElementById('ledStatus').textContent = ledStatus;
    });
}

function setAngle(axis, value) {
  fetch(`/setAngle?${axis}=${value}`)
    .then(response => response.text())
    .then(data => {
      console.log("Response from server: ", data);
      document.getElementById('range-'+axis).textContent = JSON.parse(data)[axis];
    });
}

function updateHeartbeat() {
  fetch('/heartbeat')
    .then(response => response.text())
    .then(data => {
      console.log("heartbeat received: ", data);
      document.getElementById('heartbeat').textContent = data;
    });
}

setInterval(updateHeartbeat, 1000);
