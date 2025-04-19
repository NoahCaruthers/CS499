package com.example.myapplication;

import static android.content.ContentValues.TAG;

import android.annotation.SuppressLint;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;


public class DBHandler extends SQLiteOpenHelper {
    private Context context;
    private static final String DATABASE_NAME = "inventory.db";
    private static final int VERSION = 1;

    public DBHandler(@Nullable Context context) {
        super(context, DATABASE_NAME, null, VERSION);
        this.context =  context;
    }

    private static final class InventoryTable {
        private static final String TABLE = "inventory";
        private static final String COL_ID = "_id";
        private static final String COL_NAME = "name";
        private static final String COL_DESCRIPTION = "description";
        private static final String COL_QTY = "quantity";
    }

    private static final class UserTable{
        private static final String TABLE = "users";
        private static final String COL_ID = "_id";
        private static final String COL_USERNAME = "username";
        private static final String COL_PASSWORD = "password";
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("create table " + InventoryTable.TABLE + " (" +
                InventoryTable.COL_ID + " integer primary key autoincrement, " +
                InventoryTable.COL_NAME + " text, " +
                InventoryTable.COL_DESCRIPTION + " text, " +
                InventoryTable.COL_QTY + " text)");

        db.execSQL("create table " + UserTable.TABLE + " (" +
                UserTable.COL_ID + " integer primary key autoincrement, " +
                UserTable.COL_USERNAME + " text, " +
                UserTable.COL_PASSWORD + " float)");
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("drop table if exists " + InventoryTable.TABLE);
        onCreate(db);
    }

    public void addNewItem(String itemName, String itemDescription, float itemQty){
        SQLiteDatabase db = this.getWritableDatabase();

        ContentValues values = new ContentValues();

        values.put(InventoryTable.COL_NAME,itemName );
        values.put(InventoryTable.COL_DESCRIPTION, itemDescription);
        values.put(InventoryTable.COL_QTY, itemQty);

        db.insert(InventoryTable.TABLE, null, values);
        db.close();
    }

    public void addNewUser(String userName, String userPassword){
        SQLiteDatabase db = this.getWritableDatabase();

        ContentValues values = new ContentValues();

        values.put(UserTable.COL_USERNAME,userName );
        values.put(UserTable.COL_PASSWORD, userPassword);

        db.insert(UserTable.TABLE, null, values);
        db.close();
    }
    public Boolean checkUser(String userName, String userPassword){
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.query(UserTable.TABLE, null, UserTable.COL_USERNAME + " =?", new String[]{userName}, null, null, null);

        if(cursor.moveToFirst()) {
            @SuppressLint("Range")
            String storedPassword = cursor.getString(cursor.getColumnIndex(UserTable.COL_PASSWORD));
            return userPassword.equals(storedPassword);
        }
        cursor.close();
        return Boolean.FALSE;
    }
    public void getLowQty(){
        SQLiteDatabase db = this.getReadableDatabase();

        String qty = "1";

        Cursor cursor = db.query(InventoryTable.COL_NAME,null, InventoryTable.COL_QTY + " =?",new String[]{qty},null, null, null);
        if(cursor.moveToFirst()){
            do{
                String name = cursor.getString(1);
                Log.d(TAG, "Low on hand of " + name );
            }while (cursor.moveToNext());
        }
    }
    public void deleteItem(String itemName) {
        SQLiteDatabase db = this.getWritableDatabase();

        db.delete(InventoryTable.TABLE, InventoryTable.COL_NAME + " LIKE ?", new String[]{itemName});
    }
    public void updateItem(String itemName, String itemQty){
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(InventoryTable.COL_NAME, itemName);

        db.update(InventoryTable.TABLE, values, InventoryTable.COL_QTY + " LIKE ?", new String[]{itemQty});

    }

    Cursor readAllData(){
        String query = " SELECT * FROM " + InventoryTable.TABLE;
        SQLiteDatabase db = this.getReadableDatabase();

        Cursor cursor = null;
        if(db != null){
            cursor = db.rawQuery(query, null);
        }
        return cursor;
    }

    public static class MainActivity extends AppCompatActivity {

        private Button newAccountButton, loginButton;
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

            dbHandler = new DBHandler(MainActivity.this);

            newAccountButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    String userName = usernameEdit.getText().toString();
                    String userPassword = passwordEdit.getText().toString();


                    //checks for user input, lets user know data is missing
                    if (userName.isEmpty() || userPassword.isEmpty()){
                        Toast.makeText(MainActivity.this, "Please enter all data.", Toast.LENGTH_SHORT).show();
                        return;
                    }
                    //adds new user to DB
                    dbHandler.addNewUser(userName, userPassword);

                    //confirms new user added
                    Toast.makeText(MainActivity.this, "User has been added.", Toast.LENGTH_SHORT).show();
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
                        Toast.makeText(MainActivity.this, "Please enter all data.", Toast.LENGTH_SHORT).show();
                        return;
                    }
                    Boolean checkUser = dbHandler.checkUser(userName, userPassword);

                    //checks for valid login
                    if(checkUser != Boolean.FALSE){
                        Toast.makeText(MainActivity.this, "User Verified.", Toast.LENGTH_SHORT).show();
                        Intent intent  = new Intent(getApplicationContext(), SMSNotif.class);
                        startActivity(intent);
                    }
                    //login is not valid
                    else{
                        Toast.makeText(MainActivity.this, "Invalid Login.", Toast.LENGTH_SHORT).show();
                    }

                }
            });
        }
    }
}
