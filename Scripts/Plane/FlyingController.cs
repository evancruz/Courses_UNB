using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class FlyingController : MonoBehaviour {
    private float rotationAngleDegree;
    private float rotationSpeedDegree;
    int rotationDirection;
    private Vector3 motionVelocity;
    private float motionSpeedXZ;   
    private float motionDirectionXZ;
    private float motionSpeedY;
    private int motionDirectionY;
    public GameController gameController;
    private bool inGap;
    private bool gameOn;
    

    void Start() {
        rotationAngleDegree = 0;
        rotationSpeedDegree = 75;
        rotationDirection = 0;
        motionVelocity = Vector3.zero;
        motionSpeedXZ = 13;
        motionSpeedY = 8f;
        motionDirectionY = 0;
        motionDirectionXZ = 5f;
        move();
    }

    
    void Update() {
        motionDirectionXZ = 1f;
        move();
        if (Input.GetKey("right")) {
            rotationDirection = 1;
            Rotate();
        }
        if (Input.GetKey("left")) {
            rotationDirection = -1;
            Rotate();
        }
        if (Input.GetKey("up")) {
            motionDirectionY = 1;
            move();
        }

        if (Input.GetKey("down")) {
            motionDirectionY = -1;
            move();
        }
    }

    private void Rotate() {
        float rotationVelocityDegree = rotationSpeedDegree * rotationDirection;
        rotationAngleDegree += rotationVelocityDegree * Time.deltaTime;

        //make sure that rotationAngleDegree within 0-360
        rotationAngleDegree = (rotationAngleDegree + 360) % 360; 
        transform.Rotate(Vector3.up, rotationVelocityDegree * Time.deltaTime); //Vector.up is Y-Axis
    }

    private void move() {
        //convert degree to radian
        double rotationAngleRadian = ((float)rotationAngleDegree / 360.0) * (Math.PI * 2.0); 
        float motionX = (float)Math.Sin(rotationAngleRadian) * motionDirectionXZ;
        float motionZ = (float)Math.Cos(rotationAngleRadian) * motionDirectionXZ;
        float motionY = motionDirectionY;

        motionVelocity = new Vector3(motionX, motionY, motionZ);

        //nomoralized vector to represent the directions of motionVelocity
        motionVelocity.Normalize(); 

        motionVelocity = new Vector3(motionVelocity.x * motionSpeedXZ, motionVelocity.y * motionSpeedY, motionVelocity.z * motionSpeedXZ);
        transform.position += motionVelocity * Time.deltaTime;

        rotationDirection = 0;
        motionDirectionXZ = 0;
    }

    void OnTriggerEnter(Collider c) {
    if (c.gameObject.tag == "Obstacle") {
        // gameOn = false;
        gameController.GameOver();
    } else if (c.gameObject.tag == "Ground") {
        // gameOn = false; 
        gameController.GameOver();  
    }
    if (c.gameObject.tag == "Gap") {
        inGap = true;
    }
}

    void OnTriggerExit(Collider c){
        if (inGap) {
            inGap = false;

            //note the line below is necessary to access the whole Prefab
            //obstacle object. The collider that is return only refer to the 
            //the gap cube
            GameObject parentObject = c.gameObject.transform.parent.gameObject;
            
            //call the score method with the correct obstacle and
            //a reference to this FlyingCraft object
            gameController.Score(parentObject, gameObject);
        }
    }
}
