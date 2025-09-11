#include <climits>
#include <algorithm>
#define BUCKET_SIZE 512
#define MAX_STREAMER 200000

using namespace std;

int subscriber[MAX_STREAMER / BUCKET_SIZE + 1][BUCKET_SIZE];
int bucket_sum[MAX_STREAMER / BUCKET_SIZE + 1];
int bucket_max[MAX_STREAMER / BUCKET_SIZE + 1];
int bucket_min[MAX_STREAMER / BUCKET_SIZE + 1];

int N;

void init(int N, int mSubscriber[]) {
	// set streamer count
	::N = N;

	// reset container
	for (int i = 0; i < N / BUCKET_SIZE + 1; i++) {
		bucket_sum[i] = 0;
		bucket_max[i] = 0;
		bucket_min[i] = INT_MAX;
	}

	// fill in subscriber list
	for (int i = 0; i < N; i++) {
		// assign
		subscriber[i / BUCKET_SIZE][i % BUCKET_SIZE] = mSubscriber[i];

		// increment sum
		bucket_sum[i / BUCKET_SIZE] += mSubscriber[i];

		// update max&min
		if (bucket_max[i / BUCKET_SIZE] < mSubscriber[i]) {
			bucket_max[i / BUCKET_SIZE] = mSubscriber[i];
		}
		if (bucket_min[i / BUCKET_SIZE] > mSubscriber[i]) {
			bucket_min[i / BUCKET_SIZE] = mSubscriber[i];
		}
	}

	return;
}

int subscribe(int mId, int mNum) {
	mId--;
	// update min
	// mId is the min. Need to re-iterate.
	if (bucket_min[mId / BUCKET_SIZE] == subscriber[mId / BUCKET_SIZE][mId % BUCKET_SIZE]) {
		subscriber[mId / BUCKET_SIZE][mId % BUCKET_SIZE] += mNum;
		int min = subscriber[mId / BUCKET_SIZE][0];
		for (int i = 1; i < BUCKET_SIZE; i++) {
			if (subscriber[mId / BUCKET_SIZE][i] < min) min = subscriber[mId / BUCKET_SIZE][i];
		}
		bucket_min[mId / BUCKET_SIZE] = min;
	}

	// not min, does not affect
	else {
		subscriber[mId / BUCKET_SIZE][mId % BUCKET_SIZE] += mNum;

	}

	// increment sum
	bucket_sum[mId / BUCKET_SIZE] += mNum;

	// update max
	if (bucket_max[mId / BUCKET_SIZE] < subscriber[mId / BUCKET_SIZE][mId % BUCKET_SIZE]) {
		bucket_max[mId / BUCKET_SIZE] = subscriber[mId / BUCKET_SIZE][mId % BUCKET_SIZE];
	}

	return subscriber[mId / BUCKET_SIZE][mId % BUCKET_SIZE];
}

int unsubscribe(int mId, int mNum) {
	mId--;
	// update max
	// mId is the max. Need to re-iterate.
	if (bucket_max[mId / BUCKET_SIZE] == subscriber[mId / BUCKET_SIZE][mId % BUCKET_SIZE]) {
		subscriber[mId / BUCKET_SIZE][mId % BUCKET_SIZE] -= mNum;
		int max = subscriber[mId / BUCKET_SIZE][0];
		for (int i = 1; i < BUCKET_SIZE; i++) {
			if (subscriber[mId / BUCKET_SIZE][i] > max) max = subscriber[mId / BUCKET_SIZE][i];
		}
		bucket_max[mId / BUCKET_SIZE] = max;
	}

	// not max, does not affect
	else {
		subscriber[mId / BUCKET_SIZE][mId % BUCKET_SIZE] -= mNum;

	}

	// decrement sum
	bucket_sum[mId / BUCKET_SIZE] -= mNum;

	// update min
	if (bucket_min[mId / BUCKET_SIZE] > subscriber[mId / BUCKET_SIZE][mId % BUCKET_SIZE]) {
		bucket_min[mId / BUCKET_SIZE] = subscriber[mId / BUCKET_SIZE][mId % BUCKET_SIZE];
	}

	return subscriber[mId / BUCKET_SIZE][mId % BUCKET_SIZE];
}

int count(int sId, int eId) {
	int result = 0;
	sId--;
	eId--;
	int fs = sId / BUCKET_SIZE;
	int fe = eId / BUCKET_SIZE;
	
	// add full sum
	for (int i = fs; i <= fe; i++) {
		result += bucket_sum[i];
	}

	// if in single bucket...
	if (fs == fe) {
		result = 0;
		for (int i = sId; i <= eId; i++) {
			result += subscriber[i / BUCKET_SIZE][i % BUCKET_SIZE];
		}
		return result;
	}

	// remove unnecessary start
	while (true) {
		// there is nothing to remove
		if (sId % BUCKET_SIZE == 0) break;
		else {
			sId--;
			result -= subscriber[sId / BUCKET_SIZE][sId % BUCKET_SIZE];
		}
	}

	// remove unnecessary end
	while (true) {
		if (eId % BUCKET_SIZE == BUCKET_SIZE - 1) break;
		else {
			eId++;
			result -= subscriber[eId / BUCKET_SIZE][eId % BUCKET_SIZE];
		}
	}
	return result;
}

int calculate(int sId, int eId) {
	int min_res = INT_MAX;
	int max_res = 0;
	sId--;
	eId--;
	int fs;
	int fe;
	if (sId % BUCKET_SIZE == 0) {
		fs = sId / BUCKET_SIZE;
	}
	else {
		fs = sId / BUCKET_SIZE + 1;
	}

	if (eId % BUCKET_SIZE == BUCKET_SIZE - 1) {
		fe = eId / BUCKET_SIZE;
	}
	else {
		fe = eId / BUCKET_SIZE - 1;
	}

	// if single bucket...
	if (sId / BUCKET_SIZE == eId / BUCKET_SIZE) {
		for (int i = sId; i <= eId; i++) {
			min_res = min(min_res, subscriber[i / BUCKET_SIZE][i % BUCKET_SIZE]);
			max_res = max(max_res, subscriber[i / BUCKET_SIZE][i % BUCKET_SIZE]);
		}
		return max_res - min_res;
	}


	// find max/min in full ones
	for (int i = fs; i <= fe; i++) {
		min_res = min(min_res, bucket_min[i]);
		max_res = max(max_res, bucket_max[i]);
	}

	// compare start
	while (true) {
		// there is nothing to remove
		if (sId % BUCKET_SIZE == 0) break;
		else {
			min_res = min(min_res, subscriber[sId / BUCKET_SIZE][sId % BUCKET_SIZE]);
			max_res = max(max_res, subscriber[sId / BUCKET_SIZE][sId % BUCKET_SIZE]);
			sId++;
		}
	}

	// compare end
	while (true) {
		if (eId % BUCKET_SIZE == BUCKET_SIZE - 1) break;
		else {
			min_res = min(min_res, subscriber[eId / BUCKET_SIZE][eId % BUCKET_SIZE]);
			max_res = max(max_res, subscriber[eId / BUCKET_SIZE][eId % BUCKET_SIZE]);
			eId--;
		}
	}

	return max_res - min_res;
}