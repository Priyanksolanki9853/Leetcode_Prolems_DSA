# Write your MySQL query statement below
SElECT tweet_id
FROM Tweets
WHERE CHAR_LENGTH(content) > 15;