package com.example.myapplication;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class LoginActivity extends AppCompatActivity {

    private Button newAccountButton, loginButton, addItem;
    private EditText usernameEdit, passwordEdit;
    private DBHandler dbHandler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.login_screen);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;

        });

        usernameEdit = findViewById(R.id.editUsername);
        passwordEdit = findViewById(R.id.editPassword);
        newAccountButton = findViewById(R.id.newAccount);
        loginButton = findViewById(R.id.buttonLogin);


        dbHandler = new DBHandler(LoginActivity.this);

        newAccountButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String userName = usernameEdit.getText().toString();
                String userPassword = passwordEdit.getText().toString();


                //checks for user input, lets user know data is missing
                if (userName.isEmpty() || userPassword.isEmpty()){
                    Toast.makeText(LoginActivity.this, "Please enter all data.", Toast.LENGTH_SHORT).show();
                    return;
                }
                //adds new user to DB
                dbHandler.addNewUser(userName, userPassword);

                //confirms new user added
                Toast.makeText(LoginActivity.this, "User has been added.", Toast.LENGTH_SHORT).show();
                usernameEdit.setText("");
                passwordEdit.setText("");
            }
        });

        loginButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String userName = usernameEdit.getText().toString();
                String userPassword = passwordEdit.getText().toString();

                //checks for user input, lets user know data is missing
                if (userName.isEmpty() || userPassword.isEmpty()) {
                    Toast.makeText(LoginActivity.this, "Please enter all data.", Toast.LENGTH_SHORT).show();
                    return;
                }
                Boolean checkUser = dbHandler.checkUser(userName, userPassword);

                //checks for valid login
                if(checkUser != Boolean.FALSE){
                    Toast.makeText(LoginActivity.this, "User Verified.", Toast.LENGTH_SHORT).show();
                    Intent intent  = new Intent(getApplicationContext(), SMSNotif.class);
                    startActivity(intent);
                }
                //login is not valid
                else{
                    Toast.makeText(LoginActivity.this, "Invalid Login.", Toast.LENGTH_SHORT).show();
                }

            }


        });
    }
}

