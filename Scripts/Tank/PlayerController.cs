using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerController : MonoBehaviour {
    private Vector3 velocity;
    private SpriteRenderer rend;
    public float speed = 2.0f;
    public GameObject bullet;
    private bool canFire;
    private int health;
    public GameController gameController;
    public Text healthIndicator;

    void Start() {
        velocity = new Vector3(0f, 0f, 0f);
        rend = GetComponent<SpriteRenderer> ();
        canFire = true;
        health = 3;
    }

    // Update is called once per frame
    void Update() {

        var dist = (transform.position - Camera.main.transform.position).z;
        var leftBorder = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, dist)).x;
        var rightBorder = Camera.main.ViewportToWorldPoint(new Vector3(1, 0, dist)).x;
        var bottomBorder = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, dist)).y;
        var topBorder = Camera.main.ViewportToWorldPoint(new Vector3(0, 1, dist)).y;
    
        float width = rend.bounds.size.x;
        float height = rend.bounds.size.y;

        //get left/right
        velocity = new Vector3(0f,  Input.GetAxis("Horizontal")* -1f, 0f); 

        if((transform.position.x <= leftBorder + width/2.0) && velocity.x < 0f){
            velocity = new Vector3(0f, 0f, 0f);
        }
        if((transform.position.x >= rightBorder - width/2.0) && velocity.x > 0f){
            velocity = new Vector3(0f, 0f, 0f);
        }
        if((transform.position.y <= bottomBorder + height/2.0) && velocity.y < 0f){
                velocity = new Vector3(0f, 0f, 0f);
        }
        if((transform.position.y >= topBorder - height/2.0) && velocity.y > 0f){
            velocity = new Vector3(0f, 0f, 0f);
        }
        // transform.position = transform.position + velocity * Time.deltaTime * speed;
        transform.Translate(velocity* Time.deltaTime * speed);


        if (Input.GetButtonDown("Fire1") && canFire) {
            //the offset 
            Vector3 offset = new Vector3(0f, 2f, 0f);

            //create a bullet pointing in its natural direction 
            GameObject b = Instantiate(bullet, new Vector3(0f, 0f, 0f), Quaternion.identity);

            b.GetComponent<BulletController>().InitPosition(transform.position + offset, new Vector3(0f, 2f, 0f));
            canFire = false;

            //this starts a coroutine... a non-blocking function
            StartCoroutine(PlayerCanFireAgain());
        }



        //if(Input.GetKey("mouse 0"))
        //{
        //    Instantiate(bullet, new Vector3(0f, 0f, -1f), Quaternion.identity);
        //    bullet.InitPosition(transform.position.x, new Vector3(0f, 1f, -1f););
        //}

    }

    IEnumerator PlayerCanFireAgain() {
        //this will pause the execution of this method for 3 seconds without blocking
        yield return new WaitForSecondsRealtime(3);
        canFire = true;
    }

        void OnTriggerEnter2D(Collider2D other) {
            healthIndicator.text += "X";
            health--;
            if(health == 0){
                gameController.gameOver(gameObject.name);
                Destroy(gameObject);   
            }
        }


}
