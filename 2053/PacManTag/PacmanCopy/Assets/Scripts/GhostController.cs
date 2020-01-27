using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

public class GhostController : MonoBehaviour
{
    private Vector3 velocity;

    private SpriteRenderer rend;
    private Animator anim;
    public float speed = 2.0f;

    // Use this for initialization
    void Start()
    {
        rend = GetComponent<SpriteRenderer> ();
        anim = GetComponent<Animator>();
        float xVel = Random.Range(-1, 1);
        float yVel = 0;
        if(xVel == 0){
            while(yVel == 0)
                yVel = Random.Range(-1, 1);
        }
        velocity = new Vector3(xVel, yVel, 0);
        animDirection(velocity.x, velocity.y);
    }

    // Update is called once per frame
    void Update()
    {

       // calculate location of screen borders
        // this will make more sense after we discuss vectors and 3D
        var dist = (transform.position - Camera.main.transform.position).z;
        var leftBorder = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, dist)).x;
        var rightBorder = Camera.main.ViewportToWorldPoint(new Vector3(1, 0, dist)).x;
        var bottomBorder = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, dist)).y;
        var topBorder = Camera.main.ViewportToWorldPoint(new Vector3(0, 1, dist)).y;
        
        //get the width of the object
        float width = rend.bounds.size.x;
        float height = rend.bounds.size.y;

        //set the direction based on  input
        /*if (Input.GetKey("left"))
        {
            velocity = new Vector3(-1f, 0f, 0f);  
            anim.Play("PacManLeft"); */

         //1% of the time, switch the direction: 
        int change = Random.Range(0,100);
        if (change == 0)
        {
            velocity = new Vector3(-velocity.x, -velocity.y, 0);
        }
        //1% of the time, switch from horizontal to vertical, or vice-versa: 
        else if (change == 1)
        {
            if (velocity.x != 0f)
                velocity = new Vector3(0f, velocity.x, 0f);
            else
                velocity = new Vector3(velocity.y, 0f, 0f);
        } 

        //make sure the obect is inside the borders... if edge is hit reverse direction
        if((transform.position.x <= leftBorder + width/2.0) && velocity.x < 0f){
            velocity = new Vector3(-velocity.x, 0f, 0f);
        }
        if((transform.position.x >= rightBorder - width/2.0) && velocity.x > 0f){
            velocity = new Vector3(-velocity.x, 0f, 0f);
        }
        if((transform.position.y <= bottomBorder + height/2.0) && velocity.y < 0f){
                velocity = new Vector3(0f, -velocity.y, 0f);
        }
        if((transform.position.y >= topBorder - height/2.0) && velocity.y > 0f){
            velocity = new Vector3(0f, -velocity.y, 0f);
        }
        transform.position = transform.position + velocity * Time.deltaTime * speed;
        animDirection(velocity.x,velocity.y);
    }

    void animDirection(float x, float y){
        if (x < 0) {
            anim.Play("GhostLeft");
        } else if (x > 0){
            anim.Play("GhostRight");
        } else if (y < 0) {
            anim.Play("GhostDown");
        } else {
            anim.Play("GhostUp");
        }
    }
}
