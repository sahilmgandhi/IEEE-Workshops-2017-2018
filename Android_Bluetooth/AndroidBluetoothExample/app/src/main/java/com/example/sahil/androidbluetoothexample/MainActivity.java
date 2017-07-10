package com.example.sahil.androidbluetoothexample;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.support.v7.app.AppCompatActivity;
import android.bluetooth.BluetoothAdapter;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

import android.os.Handler;

public class MainActivity extends AppCompatActivity {

    private final UUID PORT_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"); //Serial Port Service ID ... fixed value!
    // private final String DEVICE_ADDRESS="20:13:10:15:33:66";             // This is the bluetooth address of your bluetooth module
    private TextView recText;
    private Button startB, sendB, clearB, stopB;
    private EditText sendText, nameText;
    boolean buttonState, stopThread;
    Thread signalThread;
    private BluetoothDevice device;
    private BluetoothSocket socket;
    private OutputStream outputStream;
    private InputStream inputStream;
    private String btName = "SahilBT";
    byte buffer[];


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.content_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        startB = (Button) findViewById(R.id.startButton);
        sendB = (Button) findViewById(R.id.sendButton);
        clearB = (Button) findViewById(R.id.clearText);
        stopB = (Button) findViewById(R.id.stopButton);
        recText = (TextView) findViewById(R.id.receiveText);
        sendText = (EditText) findViewById(R.id.BTSend);
        nameText = (EditText) findViewById(R.id.BTName);
        recText.setMovementMethod(new ScrollingMovementMethod());
        buttonState = false;
        stopThread = false;
        setButtons(buttonState);
    }

    private void setButtons(boolean b) {
        startB.setEnabled(!b);
        sendB.setEnabled(b);
        clearB.setEnabled(b);
        stopB.setEnabled(b);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    public boolean BlueToothInit() {
        boolean foundBT = false;
        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (bluetoothAdapter == null) {
            Toast.makeText(getApplicationContext(), "Your device does not support bluetooth", Toast.LENGTH_LONG).show();
            return foundBT;
        }

        if (bluetoothAdapter.isEnabled()) {
            Intent enableAdapter = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableAdapter, 0);
            try {
                signalThread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        } else {
            return foundBT;
        }
        Set<BluetoothDevice> foundDevices = bluetoothAdapter.getBondedDevices();
        if (foundDevices.isEmpty())
            Toast.makeText(getApplicationContext(), "Please turn on the device and make sure it is within range", Toast.LENGTH_LONG).show();
        else {
            for (BluetoothDevice it : foundDevices) {
                if (it.getName().equals(nameText.getText().toString())) {     // or it.getAddress().equals(DEVICE_ADDRESS) if you are connecting via the bluetooth address
                    device = it;
                    foundBT = true;
                    break;
                }
            }
        }
        return foundBT;
    }

    public boolean BlueToothConnect() {
        boolean connected = true;
        try {
            socket = device.createInsecureRfcommSocketToServiceRecord(PORT_UUID);
            socket.connect();
        } catch (IOException e) {
            e.printStackTrace();
            connected = false;
        }
        if (connected) {
            try {
                outputStream = socket.getOutputStream();
            } catch (IOException e) {
                Toast.makeText(getApplicationContext(), "Could not set up the output stream", Toast.LENGTH_LONG).show();
                e.printStackTrace();
                connected = false;
            }
            try {
                inputStream = socket.getInputStream();
            } catch (IOException e) {
                Toast.makeText(getApplicationContext(), "Could not set up the input stream", Toast.LENGTH_LONG).show();
                e.printStackTrace();
                connected = false;
            }
        }
        return connected;
    }


    void beginListeningForData() {
        final Handler handler = new Handler();
        stopThread = false;
        buffer = new byte[1024];
        Thread thread = new Thread(new Runnable() {
            public void run() {
                while (!Thread.currentThread().isInterrupted() && !stopThread) {
                    try {
                        int byteCount = 0;
                        try {
                            byteCount = inputStream.available();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        if (byteCount > 0) {
                            byte[] rawBytes = new byte[byteCount];
                            try {
                                inputStream.read(rawBytes);
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            final String s = new String(rawBytes, "UTF-8");
                            handler.post(new Runnable() {
                                @Override
                                public void run() {
                                    recText.append(s);
                                }
                            });
                        }
                    } catch (IOException ex) {
                        ex.printStackTrace();
                        stopThread = true;
                    }
                }
            }
        });
        thread.start();
    }

    public void onClickStart(View view) {
        if (BlueToothInit()) {
            if (BlueToothConnect()) {
                buttonState = true;
                setButtons(buttonState);
                beginListeningForData();
                recText.append("\nConnection Opened!\n");
            }
        } else {
            Toast.makeText(getApplicationContext(), "Could not make the connection to the specified host!", Toast.LENGTH_SHORT).show();
            recText.append("\nCould not make connection to host specified by that name");
        }
    }

    public void onClickSend(View view) {
        String s = sendText.getText().toString();
        s.concat("\r\n");
        try {
            outputStream.write(s.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
        recText.append("\nSentData: " + s + "\n");
    }

    public void onClickStop(View view) throws IOException {
        outputStream.close();
        inputStream.close();
        socket.close();
        buttonState = false;
        stopThread = false;
        setButtons(buttonState);
        recText.append("\nConnection closed\n");
    }

    public void onClickClear(View view) {
        recText.setText("");
    }

}
