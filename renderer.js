const { exec } = require('child_process');
const path = require('path');

const exePath = path.join(__dirname, 'Bank.exe');

function createAccount() {
  const acc = document.getElementById('acc').value;
  const pw = document.getElementById('pw').value;

  exec(`"${exePath}" create ${acc} ${pw}`, (err, stdout, stderr) => {
    document.getElementById('output').innerText = err ? stderr : stdout || "Account created.";
  });
}

function deposit() {
  const acc = document.getElementById('dacc').value;
  const amt = document.getElementById('damount').value;

  exec(`"${exePath}" deposit ${acc} ${amt}`, (err, stdout, stderr) => {
    document.getElementById('output').innerText = err ? stderr : stdout || "Deposit complete.";
  });
}

function withdraw() {
  const acc = document.getElementById('wacc').value;
  const pw = document.getElementById('wpw').value;
  const amt = document.getElementById('wamount').value;

  exec(`"${exePath}" withdraw ${acc} ${pw} ${amt}`, (err, stdout, stderr) => {
    document.getElementById('output').innerText = err ? stderr : stdout || "Withdrawal complete.";
  });
}
