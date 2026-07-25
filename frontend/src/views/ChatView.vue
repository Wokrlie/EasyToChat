<template>
  <div class="chat-container">
    <div class="message-area">
      <div v-for="msg in messages" :key="msg.id" class="message-item" :class="getMessageClass(msg)">
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
      <textarea
        id="chat-entry-area"
        v-model="entryText"
        cols="50"
        placeholder="Type your message here..."
        @keydown.enter.prevent="sendMessage"
      ></textarea>
      <button class="send-button" @click="sendMessage">
        <svg viewBox="0 0 20 20" width="20" height="20" fill="currentColor">
          <path d="M2.01 21L23 12 2.01 3 2 10l15 2-15 2z" />
        </svg>
      </button>
    </div>
  </div>
</template>

<script setup lang="ts">
import { nextTick, onMounted, ref } from 'vue'
import { useUserStore } from '@/stores/user'
import type { Message } from '@/types/message'
import { chatApi } from '@/api/chatApi'

const entryText = ref('')
const messages = ref<Message[]>([])
const messageAreaRef = ref<HTMLElement | null>(null)

const userStore = useUserStore()

const getMessageClass = (msg: Message) => {
  if (msg.sender_type === 'user') {
    if (msg.sender_name === userStore.username_) return 'message-own'
    else return 'message-others'
  }
  if (msg.sender_type === 'system') return 'message-system'
}

const scrollToBottom = () => {
  nextTick(() => {
    if (messageAreaRef.value) {
      messageAreaRef.value.scrollTop = messageAreaRef.value.scrollHeight
    }
  })
}

const sendMessage = async () => {
  const content = entryText.value.trim()
  if (!content) return

  const tempMsg: Message = {
    id: Date.now(),
    sender_type: 'user',
    sender_name: 'Me',
    content: content,
    timestamp: new Date().toISOString(),
  }
  messages.value.push(tempMsg)
  entryText.value = ''
  scrollToBottom()

  try {
    await chatApi.sendMessage(content, userStore.nickname)
    await fetchMessages()
  } catch (error) {
    console.error('Failed to send message: ', error)
  }
}

const fetchMessages = async () => {
  try {
    const response = await chatApi.getMessages()
    messages.value = response.data
    scrollToBottom()
  } catch (error) {
    console.error('Failed to fetch the messages: ', error)
  }
}

onMounted(() => {
  fetchMessages()
})
</script>

<style scoped>
.chat-container {
  display: flex;
  flex-direction: column;
  height: 100%;
  padding: 10px;
  overflow: hidden;
  box-sizing: border-box;
}

.message-area {
  flex: 1;
  display: flex;
  flex-direction: column;
  overflow-y: auto;
  overflow-x: hidden;
}

.message-item {
  display: flex;
  flex-direction: row;
  max-width: 80%;
  animation: fadeIn 0.2s ease;
}

.message-others {
  align-self: flex-start;
  align-items: flex-start;
}

.message-own {
  align-self: flex-end;
  align-items: flex-end;
}

.message-sender {
  font-size: 13px;
  font-weight: 600;
  color: #555;
  margin-bottom: 4px;
  padding: 0 4px;
}

.message-own .message-sender {
  color: #2e7d32;
}

.message-bubble {
  padding: 10px 14px;
  border-radius: 18px;
  word-break: break-word;
  box-shadow: 0 1px 3px rgba(0, 0, 0, 0.08);
  max-width: 100%;
  position: relative;
}

.message-own .message-bubble {
  background: #dcf8c6;
  border-top-right-radius: 4px;
  color: #1e1e1e;
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

.message-content {
  font-family:
    system-ui,
    -apple-system,
    monospace;
  font-size: 14px;
}

.input-area {
  position: relative;
}

#chat-entry-area {
  flex: 0 0 35%;
  width: 100%;
  height: auto;
  min-height: 60px;
  padding: 12px 80px 12px 12px;
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

.send-button {
  position: absolute;
  bottom: 12px;
  right: 12px;
  padding: 8px 16px;

  background: #4caf50;
  color: white;
  border-radius: 6px;
  cursor: pointer;
  font-size: 14px;
  transition: background-color 0.2s;
  z-index: 1;
}

.send-button:hover {
  background: #45a049;
}
</style>
