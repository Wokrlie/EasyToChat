<template>
<div class="chat-container">
  <div class="message-area">
    <div
      v-for="msg in messages"
      :key="msg.id"
      class="message-item"
      :class="{ 'message-own': msg.sender_type === 'user', 'message-system': msg.sender_type === 'system'}"
      >
        <div v-if="msg.sender_type === 'system'" class="system-text">
          {{ msg.content }}
        </div>
        <div v-else>
          <div class="message-sender">{{ msg.sender_name }}</div>
          <div class="message-bubble">
            <div class="message-content">{{ msg.content }}</div>
          </div>
        </div>
      </div>
  </div>
  <div class="input-area">
    <textarea id="chat-entry-area"
      v-model="entryText"
      cols="50"
      placeholder="Type your message here...(Shift+Enter to next line)"
      @keydown.enter.prevent = "sendMessage"
    ></textarea>
    <button class="send-button" @click="sendMessage">Send</button>
  </div>
</div>
</template>

<script setup lang="ts">
import { nextTick, onMounted, ref } from 'vue'
import type { Message } from '@/types/message'
import { chatApi } from '@/api/chatApi';

const entryText = ref('');
const messages = ref<Message[]>([]);
const messageAreaRef = ref<HTMLElement | null>(null);

const scrollToBottom = () => {
  nextTick(() => {
    if (messageAreaRef.value) {
      messageAreaRef.value.scrollTop = messageAreaRef.value.scrollHeight;
    }
  });
};

const sendMessage = async () => {
  const content = entryText.value.trim();
  if (!content) return;

  const tempMsg: Message = {
    id: Date.now(),
    sender_type: "user",
    sender_name: "Me",
    content: content,
    timestamp: new Date().toISOString(),
  };
  messages.value.push(tempMsg);
  entryText.value = '';
  scrollToBottom();

  try {
    await chatApi.sendMessage(content);
    await fetchMessages();
  } catch (error) {
    console.error("Failed to send message: ", error);
  }
}

const fetchMessages = async () => {
  try {
    const response = await chatApi.getMessages();
    messages.value = response.data;
    scrollToBottom();
  } catch (error) {
    console.error("Failed to fetch the messages: ", error);
  }
}

onMounted(() => {
  fetchMessages();
});
</script>

<style scoped>
.chat-container {
  display: flex;
  flex-direction: column;
  height: 100%;
  padding: 10px;
  overflow: hidden;
}

.message-area {
  flex: 1;
  display: flex;
  flex-direction: column;
  overflow-y: auto;
  overflow-x: hidden;
}

.message-system {
  align-self: center;
}

.message-system .system-text {
  color: #888;
  font-size: 14px;
  background: transparent;
  padding: 4px 12px;
}

.message-bubble {
  border-color: #abf;
  border-radius: 10px;
}

.message-content {
  font-family: system-ui, -apple-system, monospace;
  font-size: 14px;
}

#chat-entry-area {
  flex: 0 0 35%;
  width: 100%;
  height: auto;
  min-height: 60px;
  padding: 12px;
  resize: vertical;
  outline: none;
  box-sizing: border-box;

  transition: border-color 0.3s;
  border: 2px solid #ccc;
  border-radius: 8px;
  font-size: 16px;
}

#chat-entry-area:focus {
  border-color: #4caf50;
  box-shadow: 0 0 0 4px rgba(76, 175, 80, 0.15);
}

#chat-entry-area::placeholder {
  color: #aaa;
  font-style: italic;
}
</style>
