using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallController : MonoBehaviour {

    Rigidbody rb;
    Vector3 initForce;
    
    public AudioSource myAudio;
    

    // Use this for initialization
    void Start () {
        rb = GetComponent<Rigidbody>();

        Vector3 forceDirection = new Vector3(Random.Range(-1f, -.5f), 0, Random.Range(-1f, -.5f));
        forceDirection.Normalize();

        float forcePower = 15;
        initForce = forcePower * forceDirection;

        //initial push onto the ball in the forceDirection with forcePower
        rb.AddForce(initForce, ForceMode.Impulse); 

        //SOUND
        myAudio = GetComponent<AudioSource>();

    }

    void OnCollisionEnter(Collision collision) {
        if(myAudio != null && !myAudio.isPlaying &&
        !myAudio.clip && myAudio.clip.loadState == AudioDataLoadState.Loaded){
            myAudio.Play();
        }
    }
}