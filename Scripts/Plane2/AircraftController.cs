using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AircraftController : MonoBehaviour {
    float circleRadius;
    float circleSpeed;
    float circleAngle;
    float selfRotationSpeed;
    Vector3 lastDirection;

    public GameController gameController;
    private bool inGap;
    
     void Start () {
        circleRadius = 10;
        circleSpeed = 0.5f;
        circleAngle = 0;
        selfRotationSpeed = 100;

        lastDirection = new Vector3(1, 0, 0);
        lastDirection.Normalize();
        moveForward();
        moveForward();
    }

    void Update() {
        //Run the program and observe how the Aircraft object moves along a circular path. 
        //It rotate around Space.World as it moves around the circle, 
        //and rotates around its own forward axis (Space.Self).
        

        // Pressing the “up” key, the Aircraft will go forward along the circular path.
        if (Input.GetKey("up")) {
            moveForward();
        }
        //Pressing the “left” or “right” keys, the object will roll left or right.
         if (Input.GetKey("left")) {
            transform.Rotate(Vector3.forward, selfRotationSpeed * Time.deltaTime, Space.Self);
        }
         if (Input.GetKey("right")) {
            transform.Rotate(Vector3.back, selfRotationSpeed * Time.deltaTime, Space.Self);
        }      
    }

    void moveForward(){
        circleAngle += circleSpeed * Time.deltaTime;
        circleAngle = (circleAngle + 360) % 360;

        float newPositionX = circleRadius * (float)Mathf.Cos(circleAngle);
        float newPositionZ = circleRadius * (float)Mathf.Sin(circleAngle);

        Vector3 newPosition = new Vector3(newPositionX, transform.position.y, newPositionZ);
        Vector3 newDirection = newPosition - transform.position;

        newDirection.Normalize();

        float rotationAngle = -Vector3.Angle(lastDirection, newDirection);
        newPositionX = circleRadius * (float)Mathf.Cos(circleAngle);
        newPositionZ = circleRadius * (float)Mathf.Sin(circleAngle);
        transform.Rotate(Vector3.up, rotationAngle, Space.World);
        transform.position = newPosition;
        lastDirection = newDirection;
    }

    void OnTriggerEnter(Collider c) {
        if (c.gameObject.tag == "Obstacle") {
            //do something
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
