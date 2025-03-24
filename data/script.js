var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

window.addEventListener('load', onLoad);

function onLoad(event) {
    initWebSocket();
    initGauges();
}

function onOpen(event) {
    console.log('Connection opened');
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

function initWebSocket() {
    console.log('Trying to open a WebSocket connection…');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

function onMessage(event) {
    console.log('Received data:', event.data);
    var data = JSON.parse(event.data);

    if (data.current !== undefined) {
        document.getElementById('current').innerHTML = data.current;
    }

    if (data.latitude !== undefined && data.longitude !== undefined) {
        document.getElementById('latitude').innerHTML = data.latitude;
        document.getElementById('longitude').innerHTML = data.longitude;
    }

    // Optional: Update Gauges (nếu có dùng JustGage hoặc lib khác)
    if (data.gauge_temp !== undefined) gauge_temp.refresh(data.gauge_temp);
    if (data.gauge_humi !== undefined) gauge_humi.refresh(data.gauge_humi);
    if (data.gauge_co2 !== undefined) gauge_co2.refresh(data.gauge_co2);

    if (data.gauge_pm1 !== undefined) gauge_pm1.refresh(data.gauge_pm1);
    if (data.gauge_pm25 !== undefined) gauge_pm25.refresh(data.gauge_pm25);
    if (data.gauge_pm4 !== undefined) gauge_pm4.refresh(data.gauge_pm4);
    if (data.gauge_pm10 !== undefined) gauge_pm10.refresh(data.gauge_pm10);
    if (data.gauge_voc !== undefined) gauge_voc.refresh(data.gauge_voc);
    if (data.gauge_nox !== undefined) gauge_nox.refresh(data.gauge_nox);

    if (data.gauge_sound !== undefined) gauge_sound.refresh(data.gauge_sound);
    if (data.gauge_vibration !== undefined) gauge_vibration.refresh(data.gauge_vibration);
    if (data.gauge_battery !== undefined) gauge_battery.refresh(data.gauge_battery);

}

function initGauges() {
    gauge_temp = new JustGage({
        id: "gauge_temp",
        value: 0,
        min: -10,
        max: 50,
        title: "Temperature (°C)",
        label: "°C",
        gaugeWidthScale: 0.6,
        pointer: true
    });

    gauge_humi = new JustGage({
        id: "gauge_humi",
        value: 0,
        min: 0,
        max: 100,
        title: "Humidity (%)",
        label: "%",
        gaugeWidthScale: 0.6,
        pointer: true
    });

    gauge_voc = new JustGage({
        id: "gauge_voc",
        value: 0,
        min: 0,
        max: 500,
        title: "VOC Index",
        label: "Index",
        gaugeWidthScale: 0.6,
        pointer: true
    });

    gauge_nox = new JustGage({
        id: "gauge_nox",
        value: 0,
        min: 0,
        max: 500,
        title: "NOx Index",
        label: "Index",
        gaugeWidthScale: 0.6,
        pointer: true
    });

    gauge_co2 = new JustGage({
        id: "gauge_co2",
        value: 400,
        min: 400,
        max: 5000,
        title: "CO2 (ppm)",
        label: "ppm",
        gaugeWidthScale: 0.6,
        pointer: true
    });

    gauge_pm1 = new JustGage({
        id: "gauge_pm1",
        value: 0,
        min: 0,
        max: 500,
        title: "PM1.0",
        label: "µg/m³",
        gaugeWidthScale: 0.6,
        pointer: true
    });

    gauge_pm25 = new JustGage({
        id: "gauge_pm25",
        value: 0,
        min: 0,
        max: 500,
        title: "PM2.5",
        label: "µg/m³",
        gaugeWidthScale: 0.6,
        pointer: true
    });

    gauge_pm4 = new JustGage({
        id: "gauge_pm4",
        value: 0,
        min: 0,
        max: 500,
        title: "PM4.0",
        label: "µg/m³",
        gaugeWidthScale: 0.6,
        pointer: true
    });

    gauge_pm10 = new JustGage({
        id: "gauge_pm10",
        value: 0,
        min: 0,
        max: 500,
        title: "PM10",
        label: "µg/m³",
        gaugeWidthScale: 0.6,
        pointer: true
    });
    gauge_sound = new JustGage({
        id: "gauge_sound",
        value: 0,
        min: 0,
        max: 120,
        title: "Sound (dB)",
        label: "dB",
        gaugeWidthScale: 0.6,
        pointer: true
    });

    gauge_vibration = new JustGage({
        id: "gauge_vibration",
        value: 0,
        min: 0,
        max: 100,
        title: "Vibration",
        label: "Index",
        gaugeWidthScale: 0.6,
        pointer: true
    });

    gauge_battery = new JustGage({
        id: "gauge_battery",
        value: 100,
        min: 0,
        max: 100,
        title: "Battery (%)",
        label: "%",
        gaugeWidthScale: 0.6,
        pointer: true
    });

}