/*
 * TCP neat congestion control
 */

#include <linux/mm.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/inet_diag.h>

#include <net/tcp.h>


/* Neat variables */
struct neat {
	u32 lastPktsAck;
	int lastActivation;
	int dupAck;
	int timeout;
};

/* Evaluate the NN. Returns new CWND */
static inline u8 tcp_neat_eval(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct neat *neat = inet_csk_ca(sk);
	// Implement NN
/*	int one = (tp->snd_cwnd>0)? 1 : 0;
	int two = (neat->lastActivation)? 1 : 0;
	int three = 1;//neat->timeout;
	int six = (0.500052+0.947995*one >0)?1:0;
	int out = (-0.728733*one - 1.76637*two + 1.43347*six + 1.5314 >0)?1:0;
	//neat->lastActivation = out;
	if(out>0){
		return 1;
	} else
		return 0;

*/
	// Implement NN logical as floats are not usable
	bool a = (tp->snd_cwnd > 0);
	bool b = (neat->dupAck>0);
	bool c = (neat->timeout>0);
	bool la = (neat->lastActivation>0);
	bool d = c || a;
	bool z = ( (!b && (d || la) ) || (b && d && la) );
	neat->lastActivation = z;
	if (z){
		return 1;
	} else {
		return 0;
	}
}


static void tcp_neat_init(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct neat *neat = inet_csk_ca(sk);
	neat->dupAck = 0;
	neat->lastActivation = 0;
	neat->timeout = 0;
	neat->lastPktsAck = 0;
	tp->snd_cwnd = 1;
}


/**
*	Executed everytime a packet is acked
*/
static void tcp_neat_pkts_acked(struct sock *sk,
				const struct ack_sample *sample)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct neat *neat = inet_csk_ca(sk);
	if (neat->lastPktsAck == 0){
		neat->lastPktsAck = sample->pkts_acked;
	} else if (neat->lastPktsAck == sample->pkts_acked){
		// The last acked pkt is the same as now acked
		// set dupAck
		neat->dupAck = 1;
	} else {
		// Connection is fine: Reset DupAck and timeout
		neat->dupAck = 0;
		neat->timeout = 0;
	}
}

/*
* Interpret the event CA_EVENT_LOSS as timeout.
*/
static void tcp_neat_cwnd_event(struct sock *sk, enum tcp_ca_event event)
{
	struct neat *neat = inet_csk_ca(sk);
	if (event == CA_EVENT_LOSS)
		neat->timeout = 1;
}

static void tcp_neat_cong_avoid(struct sock *sk, u32 ack, u32 acked)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct neat *neat = inet_csk_ca(sk);
	// DO NEAT NN
	u8 activation = tcp_neat_eval(sk);
	if (activation>0){
		tp->snd_cwnd++;
	} else if (tp->snd_cwnd >= 1){
		tp->snd_cwnd--;
	}
	
}


/**
*  Needs to be implemented:
*  simply return the current cwnd, such that it has no effect
*/
static u32 tcp_neat_ssthresh(struct sock *sk)
{
	const struct tcp_sock *tp = tcp_sk(sk);

	return tp->snd_cwnd;
}

/*
*  We dont want the cwnd to be reset
*/
static u32 tcp_neat_undo_cwnd(struct sock *sk){
	struct tcp_sock *tp = tcp_sk(sk);
	return tp->snd_cwnd;
}

static void tcp_neat_in_ack_event(struct sock *sk, u32 flags){
	struct tcp_sock *tp = tcp_sk(sk);
	struct neat *neat = inet_csk_ca(sk);
	// DO NEAT NN
	u8 activation = tcp_neat_eval(sk);
	if (activation>0){
		tp->snd_cwnd++;
	} else if (tp->snd_cwnd >= 1){
		tp->snd_cwnd--;
	}
	
}


static struct tcp_congestion_ops tcp_neat __read_mostly = {
	.init		= tcp_neat_init,
	.ssthresh	= tcp_neat_ssthresh,
	.undo_cwnd	= tcp_neat_undo_cwnd,
	.cong_avoid	= tcp_neat_cong_avoid,
	.pkts_acked	= tcp_neat_pkts_acked,
	.cwnd_event	= tcp_neat_cwnd_event,
	.in_ack_event = tcp_neat_in_ack_event,

	.owner		= THIS_MODULE,
	.name		= "neat",
};

static int __init tcp_neat_register(void)
{
	BUILD_BUG_ON(sizeof(struct neat) > ICSK_CA_PRIV_SIZE);
	tcp_register_congestion_control(&tcp_neat);
	return 0;
}

static void __exit tcp_neat_unregister(void)
{
	tcp_unregister_congestion_control(&tcp_neat);
}

module_init(tcp_neat_register);
module_exit(tcp_neat_unregister);

MODULE_AUTHOR("Kay Luis Wallaschek");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TCP Neat");
